#ifndef __TAGS_H__
#define __TAGS_H__

#include <QString>
#include <QStringList>

class Tags {

public:

	int getNumTags() { return tags.size(); }
	QString getTag(int index) { return tags[index]; }
	const QStringList& getTags() { return tags; }

	bool exist(const QString& tag) { return tags.indexOf(tag) >= 0; }

	void add(const QString& tag) { 
		if (!exist(tag))
			tags.append(tag);
	}
	
	void remove(int index) { tags.remove(index); }
	void remove(const QString& tag) {
		int index = tags.indexOf(tag);
		if (index >= 0)
			tags.remove(index);
	}

	QString toString() {
		QString result;

		for (int i = 0; i < tags.size(); i++) {
			if (i != 0)
				result += ";";
			result += tags[i];
		}

		return result;
	}

	static Tags fromString(const QString& txt) {
		QStringList list = txt.split(QLatin1Char(';'), Qt::SkipEmptyParts);
		Tags result;

		for (int i = 0; i < list.size(); i++) {
			result.add(list[i]);
		}

		return result;
	}

private:
	QStringList tags;
};


#endif /* __TAGS_H__ */
