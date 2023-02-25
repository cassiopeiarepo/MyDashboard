#include "TrivialDirExplorer.h"
#include "app/Utils/Workspace.h"

#include <QMessagebox>
#include <QDebug>

#include "app/Gui/Views/TrivialDocumentsView.h"

TrivialDirExplorer::TrivialDirExplorer() {

    model = new QFileSystemModel;

    QString str = Workspace::get()->getDir().absolutePath();
    /*
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
    */

    //model->setRootPath("d:/Workscpace");
    model->setRootPath(QDir::currentPath());
    setModel(model);
    hideColumn(1);
    hideColumn(2);
    hideColumn(3);

    //setRootIndex(model->index(QDir::currentPath()));

    QObject::connect(this, &QAbstractItemView::activated,
        this, &TrivialDirExplorer::OnActivated);

}


void TrivialDirExplorer::OnActivated(const QModelIndex& index) {
    QString path = model->filePath(index);
    //qDebug() << "path:" << path;
    TrivialDocumentsView::get()->OpenFile(path);
}
