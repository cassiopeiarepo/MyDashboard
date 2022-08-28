#include "TrivialDirExplorer.h"
#include "app/Utils/Workspace.h"

#include <QMessagebox>

TrivialDirExplorer::TrivialDirExplorer() {

    model = new QFileSystemModel;

    QString str = Workspace::get()->getDir().absolutePath();
    /*
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
    */

    model->setRootPath("d:/Workscpace");
    setModel(model);
    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
}

