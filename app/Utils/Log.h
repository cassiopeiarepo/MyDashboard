#ifndef __LOG_H__
#define __LOG_H__

#include "coreqt/Utils/Base.h"
#include "coreqt/Utils/Singleton.h"

#include <QDebug>
#include <QList>
#include <QObject>

class ILogReceiver;

QString log_file(const QString &filename, int line, int pos);



class Log : public QObject, public Singleton<Log> {
	Q_OBJECT
public:
	/*
	// info message
	void message(const char* format, ...);

	// warning
	void warning(const char* format, ...);

	// error
	void error(const char* format, ...);

	// fatal error
	void fatal(const char* format, ...);

	// info message
	void file_message(const char* filename, int line, int col, const char* format, ...);

	// warning
	void file_warning(const char* filename, int line, int col, const char* format, ...);

	// error
	void file_error(const char* filename, int line, int col, const char* format, ...);
	*/

	void registerLogReceiver( ILogReceiver* receiver);
	void unregisterLogReceiver( ILogReceiver* receiver);

/*

public slots:
	void message(const QString& msg);
	void warning(const QString& msg);
	void error(const QString& msg);
*/

private:
	QList<ILogReceiver*> receivers;
	char buffer[512];
};

class ILogReceiver {

public:
	enum Kind
	{
		MESSAGE,
		WARNING,
		ERRROR
	};

	virtual void logMessage(Kind kind, QString msg) = 0;
	virtual void logMessageFile(Kind kind, QString msg, QString file, int line, int col) = 0;

};


#endif /* __LOG_H__ */
