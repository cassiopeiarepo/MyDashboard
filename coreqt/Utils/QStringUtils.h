#ifndef __QSTRINGUTILS_H__
#define __QSTRINGUTILS_H__

#include <QString>
#include <QList>
#include <QdateTime>

class QStringUtils {
public:

	static QStringList splitLinesWindows(const QString& str);
	static QStringList splitLinesUnix(const QString& str);

	static QStringList splitLinesToVectorWindows(const QString& str);

	static bool loadStringFromFileWindows(const QString& file_path, QString& str);
	static bool loadStringFromFileUnix(const QString& file_path, QString& str);

	static bool StrToIntArray(const QString& str, int* _array, int size);
	static bool StrToFloatArray(const QString& str, float* _array, int size);

	static bool StrToFloat(const QString& str, float& value);
	static bool StrToInt(const QString& str, int& value);

	static bool StrToDuration(const QString& str, float& value);

	// RRRR/MM/DD HH:MM
	static bool StrToDateTime(const QString& str, QDateTime& value);

	// RRRR/MM/DD
	static bool StrToDate(const QString& str, QDate& value);

	// HH:MM
	static bool StrToTime(const QString& str, QTime& value);

};

#endif /* __QSTRINGUTILS_H__ */

