#include "app/Gui/Views/TrivialLogView.h"

#include <QDateTime>

const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(NULL);
TrivialLogView* TrivialLogView::log_view = NULL;

TrivialLogView::TrivialLogView(QWidget* parent) : QTreeWidget(parent) {
	log_view = this;
	qInstallMessageHandler(TrivialLogView::logMessageHandler);
	createHeaders();
}

void TrivialLogView::createHeaders() {
	setColumnCount(3);

	setHeaderLabels(QStringList() << "Time " << "Type" << "Description");
    setColumnWidth(0, 120);
    setColumnWidth(1, 60);
	setColumnWidth(2, 600);
}

void TrivialLogView::logMessageHandler(QtMsgType msg_type, const QMessageLogContext& msg_context, const QString& msg) {
	if (log_view == NULL) return;

	QTreeWidgetItem* item = new QTreeWidgetItem(log_view);
	item->setText(0, QDateTime::currentDateTime().toString("hh:mm:ss dd/MM"));
	item->setText(1, log_view->msgTypeToString(msg_type));
	item->setText(2, msg);
	log_view->addTopLevelItem(item);

	(*QT_DEFAULT_MESSAGE_HANDLER)(msg_type, msg_context, msg);
}

QString TrivialLogView::msgTypeToString(QtMsgType msg_type) {
	switch (msg_type)
	{
		case QtMsgType::QtInfoMsg: return "Info";
		case QtMsgType::QtDebugMsg: return "Debug";
		case QtMsgType::QtWarningMsg: return "Warning";
		case QtMsgType::QtCriticalMsg: return "Critical";
		case QtMsgType::QtFatalMsg: return "Fatal";
	}
	return "";
}

