#ifndef TRIVIAL_DIR_EXPLORER_H
#define TRIVIAL_DIR_EXPLORER_H

#include <QTreeView>
#include <QFileSystemModel>

class TrivialDirExplorer : public QTreeView {
	Q_OBJECT
public:

	TrivialDirExplorer();

protected:
	void OnActivated(const QModelIndex& index);

protected:
	QFileSystemModel* model;
};



#endif // TRIVIAL_DIR_EXPLORER_H