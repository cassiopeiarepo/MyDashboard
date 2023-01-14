#include "Log.h"

QString log_file(const QString& filename, int line, int pos) {
	return QString("in file \"") + filename + "\":" + QString::number(line) + ":" + QString::number(pos) + " ";
}


/*
void Log::message(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);
	fprintf(stdout, "\n");
	fflush(stdout);


	va_list argptr2;
	va_start(argptr2, format);
	vsnprintf(buffer, 512, format, argptr2);
	va_end(argptr2);

	QString msg = QString::fromUtf8(buffer);
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::MESSAGE, msg);
	}

}

void Log::warning(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);

	va_list argptr2;
	va_start(argptr2, format);
	vsnprintf(buffer, 512, format, argptr2);
	va_end(argptr2);

	QString msg = QString::fromUtf8(buffer);
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::WARNING, msg);
	}
}

void Log::error(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);

	va_list argptr2;
	va_start(argptr2, format);
	vsnprintf(buffer, 512, format, argptr2);
	va_end(argptr2);

	QString msg = QString::fromUtf8(buffer);
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::ERRROR, msg);
	}
}

void Log::fatal(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);
#ifdef NDEBUG
	exit(EXIT_FAILURE);
#else
	abort();
#endif
}


void Log::message(const QString& msg) {
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::MESSAGE, msg);
	}
}

void Log::warning(const QString& msg) {
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::WARNING, msg);
	}
}

void Log::error(const QString& msg) {
	for (ILogReceiver* receiver : receivers) {
		receiver->logMessage(ILogReceiver::ERRROR, msg);
	}
}


// info message
void Log::file_message(const char* filename, int line, int col, const char* format, ...) {
	fprintf(stdout, "%s %i, %i - ", filename, line, col);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);
	fprintf(stdout, "\n");
	fflush(stdout);
}

// warning
void Log::file_warning(const char* filename, int line, int col, const char* format, ...) {
	fprintf(stderr, "%s %i, %i - ", filename, line, col);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);
}

// error
void Log::file_error(const char* filename, int line, int col, const char* format, ...) {
	fprintf(stderr, "%s %i, %i - ", filename, line, col);

	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);
}
*/

void Log::registerLogReceiver(ILogReceiver* receiver) {
	if (receivers.indexOf(receiver) >= 0)
		return;

	receivers.append(receiver);
}

void Log::unregisterLogReceiver(ILogReceiver* receiver) {
	receivers.removeOne(receiver);
}
