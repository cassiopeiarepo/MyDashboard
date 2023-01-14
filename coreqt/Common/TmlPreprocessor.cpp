#include "TmlPreprocessor.h"
#include "app/Utils/Log.h"
#include "coreqt/Utils/QStringUtils.h"

void TmlPreprocessor::parseFile(const QString& file_path, const QString& file_type) {
	QFileInfo fi(file_path);

	if (!fi.exists()) {
		qCritical() << "TmlPreprocessor:parseFile - file not exist";
		return;
	}

	if (file_type == "c") {
		parse_c(fi);
	}
	else {
		qCritical() << "TmlPreprocessor:parseFile - unknown file type";
		return;
	}
}

void TmlPreprocessor::parseDir(const QString& dir_path, const QString& file_type) {

}

QChar TmlPreprocessor::next() {
	str_pos++;

	if (ch == QChar(TmlSource::EOL)) {
		pos = 0;
		line++;
	}
	else if (ch != QChar(TmlSource::EOS)) {
		pos++;
	}

	if (str_pos >= src_size) {
		ch = QChar(TmlSource::EOS);
		return QChar(TmlSource::EOS);
	}

	ch = input[str_pos];
	return ch;
}

QChar TmlPreprocessor::forward() {
	if (str_pos >= src_size)
		return QChar(TmlSource::EOS);
	return input[str_pos + 1];
}

void TmlPreprocessor::parse_c(const QFileInfo& fi) {

	input = "";
	if (!QStringUtils::loadStringFromFileUnix(fi.absoluteFilePath(), input)) {
		qCritical() << "TmlPreprocessor:parse_c - file not load failed";
		return;
	}

	str_pos = -1;
	src_size = input.size();
	line = 1;
	pos = 1;
	ch = ' ';

	next();
	
	while (ch != QChar(TmlSource::EOS) && ch != '/')
		next();

	if (ch == '/') {
		next();
		if (ch == '/') {
			QString line_comment;

			next();

			while (ch != QChar(TmlSource::EOS) && ch != QChar(TmlSource::EOL)) {
				line_comment += ch;
				next();
			}

		} else if (ch == '*') {
			QString multi_line_comment;

			next();

			//while (ch != TmlSource::EOS && )
		}
	}

}
