#include "TrivialDocumentsView.h"
#include <QTextEdit>


TrivialDocumentsView::TrivialDocumentsView(QWidget* parent) {

	QTextEdit* edit1 = new QTextEdit(this);
	QTextEdit* edit2 = new QTextEdit(this);

	addTab(edit1, "text1.txt");
	addTab(edit2, "workspace.xml");
}

void TrivialDocumentsView::fileNew() {

}

void TrivialDocumentsView::fileOpen() {

}

void TrivialDocumentsView::fileSave() {

}

void TrivialDocumentsView::fileSaveAs() {

}

