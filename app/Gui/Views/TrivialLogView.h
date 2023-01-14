#ifndef TRIVIAL_LOG_VIEW_H
#define TRIVIAL_LOG_VIEW_H

#include <QTreeWidget>

#include "app/Utils/Log.h"

class TrivialLogView : public QTreeWidget {
	Q_OBJECT
public:
	TrivialLogView(QWidget* parent = NULL);

	static void logMessageHandler(QtMsgType msg_type, const QMessageLogContext& msg_context, const QString& msg);

private:
	static TrivialLogView* log_view;
	void createHeaders();

	QString msgTypeToString(QtMsgType msg_type);
};

#endif
