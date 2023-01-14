#ifndef _TRIVIAL_DOCUMENTS_VIEW_H
#define _TRIVIAL_DOCUMENTS_VIEW_H

#include <QTabWidget>
#include <core/utils/Singleton.h>

class TrivialTextEditor;

class BaseFileDocument : public QObject {
Q_OBJECT
public:
	BaseFileDocument();

	virtual QString& getFilename() { return filename; }
	virtual QString& getShortname() { return shortname; }
	virtual QString& getFileType() { return filetype;  }

	virtual void fileOpen(QString &fname);

	QWidget* getWidget() { return widget; }

signals:
	void shortnameChange();

protected:
	QString filename;
	QString shortname;
	QString filetype;
	QString subtype;

	QWidget* widget;

	QString createEmptyShortName();
	QString createShortname(QString& fname);
	void setShortname(const QString& _shortname);
};

class BaseTTEFileDocument : public BaseFileDocument  {

public:
	BaseTTEFileDocument();

	void fileOpen(QString& fname) override;

protected:
	TrivialTextEditor* editor;
};

class TextTTEFileDocument : public BaseTTEFileDocument {

public:
	TextTTEFileDocument();

};

class XmlTTEFileDocument : public BaseTTEFileDocument {

public:
	XmlTTEFileDocument(QString& _subtype);


};


class TrivialDocumentsView : public QTabWidget, public Singleton<TrivialDocumentsView> {
	Q_OBJECT

public:
	TrivialDocumentsView(QWidget* parent = nullptr);

	void OpenFile(QString& path);

	void fileNew();
	void fileOpen();
	void fileSave();
	void fileSaveAs();

	int getNmmDocument() { return docs.size(); }
	BaseFileDocument* getDocument(int index) { return docs[index]; }

	BaseFileDocument* getDocumentByShortname(QString& shortname);
	BaseFileDocument* getDocumentByFilename(QString& _filename);

	void addFileType(QString& name, QString& ext, QString& type, QString& subtype);

public slots:
	void onShortnameChaneged();

public:

	class DocumentType {
	public:

		DocumentType(QString& _name, QString& _ext, QString& _type, QString& _subtype) : name(_name), ext(_ext), type(_type), subtype(_subtype) { }
		DocumentType(DocumentType& doctype) {
			name = doctype.name;
			ext = doctype.ext;
			type = doctype.type;
			subtype = doctype.subtype;
		}

		QString name;
		QString ext;
		QString type;
		QString subtype;
	};


protected:
	QList<BaseFileDocument*> docs;
	QList<DocumentType*> docs_type;

	BaseFileDocument* addDocument(DocumentType* doc_type);
	void setActiveDocument(BaseFileDocument* doc);

private:
	
};

#endif // _TRIVIAL_DOCUMENTS_VIEW_H
