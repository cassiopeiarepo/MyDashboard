#ifndef __LOG_H__
#define __LOG_H__

#include "core/types/Base.h"
#include "core/utils/Singleton.h"

class Log : public Singleton<Log> {

public:

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

};

#endif /* __LOG_H__ */
