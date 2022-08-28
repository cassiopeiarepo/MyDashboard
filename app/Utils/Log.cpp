#include "Log.h"


void Log::message(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stdout, format, argptr);
	va_end(argptr);
	fprintf(stdout, "\n");
	fflush(stdout);
}

void Log::warning(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);
}

void Log::error(const char* format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	fflush(stderr);
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