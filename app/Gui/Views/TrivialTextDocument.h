#ifndef _TRIVIAL_TEXT_DOCUMENT_H
#define _TRIVIAL_TEXT_DOCUMENT_H

#include "app/Gui/Views/TrivialTextEditor.h"
#include "app/Gui/Views/TrivialDocumentsView.h"


class TrivialDocumentBase : QObject, IFileDocument {
	Q_OBJECT
public:
	TrivialDocumentBase();

	QString getFilename() override;
	QString getShortName() override;
	QString getFileType() override;

	void FileOpen(QString& filename) override;
	void FileSave() override;
};



#endif // _TRIVIAL_TEXT_DOCUMENT_H

