#include "TrivialDocumentsView.h"
#include <QTextEdit>
#include <QFileInfo>
#include <QDebug>

#include "app/Gui/Views/TrivialTextEditor.h"

BaseFileDocument::BaseFileDocument() {

	setShortname(createEmptyShortName());

}

void BaseFileDocument::fileOpen(QString& fname) {
	QFileInfo fi(fname);

	if (!fi.exists())
		return;

	filename = fname;
	setShortname(createShortname(filename));
}

QString BaseFileDocument::createEmptyShortName() {
	QString simple_name = "Untitled";
	int index = 0;

	while (true) {
		QString shortname = simple_name + QString::number(index);
		if (TrivialDocumentsView::get()->getDocumentByShortname(shortname) == NULL) 
		{
			return shortname;
		}
		index++;
	}
	return "";
}

QString BaseFileDocument::createShortname(QString& fname) {
	QFileInfo fi(fname);
	return fi.fileName();
}

void BaseFileDocument::setShortname(const QString& _shortname) {
	shortname = _shortname;
	emit shortnameChange();
}


BaseTTEFileDocument::BaseTTEFileDocument() : BaseFileDocument() {
	editor = new TrivialTextEditor();
	widget = editor;

}

void BaseTTEFileDocument::fileOpen(QString& fname) {
	BaseFileDocument::fileOpen(fname);
	editor->getTextBuffer()->loadFile(fname);
}

TextTTEFileDocument::TextTTEFileDocument() : BaseTTEFileDocument()  {
	filetype = "text";

}

XmlTTEFileDocument::XmlTTEFileDocument(QString& _subtype) : BaseTTEFileDocument() {
	filetype = "xml";
	subtype = _subtype;

	XmlSyntaxHighliter* higliter = new XmlSyntaxHighliter(editor);
	editor->setSyntaxHighliter(higliter);
}

TrivialDocumentsView::TrivialDocumentsView(QWidget* parent) {
	setMovable(true);
}

BaseFileDocument* TrivialDocumentsView::getDocumentByShortname(QString& shortname) {
	for (int i = 0; i < docs.size(); i++) {
		if (docs[i]->getShortname() == shortname)
			return docs[i];
	}
	return NULL;
}

BaseFileDocument* TrivialDocumentsView::getDocumentByFilename(QString& _filename) {
	QFileInfo fi(_filename);

	for (int i = 0; i < docs.size(); i++) {
		if (docs[i]->getFilename() != "") {
			QFileInfo fi2(docs[i]->getFilename());
			if (fi == fi2)
				return docs[i];
		}
	}
	return NULL;
}

void TrivialDocumentsView::addFileType(QString& name, QString& ext, QString& type, QString& subtype) {
	DocumentType* doc_type = new DocumentType(name, ext, type, subtype);
	docs_type.append(doc_type);

}

void TrivialDocumentsView::OpenFile(QString& path) {
	QFileInfo fi(path);
	BaseFileDocument* file_doc = getDocumentByFilename(path);

	if (file_doc != NULL) {
		setActiveDocument(file_doc);
		return;
	}

	file_doc = NULL;

	for (int i = 0; i < docs_type.size(); i++) {
		if (docs_type[i]->ext == fi.suffix()) {
			file_doc = addDocument(docs_type[i]);
			break;
		}
	}

	if (file_doc != NULL) {
		setActiveDocument(file_doc);
		file_doc->fileOpen(path);
	}
}

BaseFileDocument* TrivialDocumentsView::addDocument(DocumentType* doc_type) {
	if (doc_type->type == "TextTTE") {
		TextTTEFileDocument* editor = new TextTTEFileDocument();
		docs.append(editor);
		addTab(editor->getWidget(), editor->getShortname());
		connect(editor, &BaseFileDocument::shortnameChange, this, &TrivialDocumentsView::onShortnameChaneged);
		return editor;
	} else if (doc_type->type == "XmlTTE") {
		XmlTTEFileDocument* editor = new XmlTTEFileDocument(doc_type->subtype);
		docs.append(editor);
		addTab(editor->getWidget(), editor->getShortname());
		connect(editor, &BaseFileDocument::shortnameChange, this, &TrivialDocumentsView::onShortnameChaneged);
		return editor;
	}

	return NULL;
}

void TrivialDocumentsView::onShortnameChaneged() {

	BaseFileDocument* file_document = qobject_cast<BaseFileDocument*>(sender());

	if (file_document != NULL) {
		int index = docs.indexOf(file_document);
		if (index >= 0) {
			QWidget* _widget = docs[index]->getWidget();

			int index = -1;

			for (int i = 0; i < count(); i++) {
				if (widget(i) == _widget) {
					index = i;
					break;
				}
			}

			if (index >= 0) {
				setTabText(index, file_document->getShortname());
			}

		}
	}

}

void TrivialDocumentsView::setActiveDocument(BaseFileDocument* doc) {
	if (doc == NULL)
		return;

	QWidget* _widget = doc->getWidget();

	int index = -1;

	for (int i = 0; i < count(); i++) {
		if (widget(i) == _widget) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		setCurrentIndex(index);
	}
}

void TrivialDocumentsView::fileNew() {

}

void TrivialDocumentsView::fileOpen() {

}

void TrivialDocumentsView::fileSave() {

}

void TrivialDocumentsView::fileSaveAs() {

}



