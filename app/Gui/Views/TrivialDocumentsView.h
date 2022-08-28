#ifndef _TRIVIAL_DOCUMENTS_VIEW_H
#define _TRIVIAL_DOCUMENTS_VIEW_H

#include <QTabWidget>
#include <core/types/Vector.h>


class IFileDocument {
public:
	virtual QString getFilename() = 0;
	virtual QString getShortName() = 0;
	virtual QString getFileType() = 0;

	virtual void FileOpen(QString& filename) = 0;
	virtual void FileSave() = 0;

};



class TrivialDocumentsView : public QTabWidget {
	Q_OBJECT

public:
	TrivialDocumentsView(QWidget* parent = nullptr);

	void fileNew();
	void fileOpen();
	void fileSave();
	void fileSaveAs();

protected:
	Vector<IFileDocument*> docs;
};

#endif // _TRIVIAL_DOCUMENTS_VIEW_H
