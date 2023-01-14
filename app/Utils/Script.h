#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "coreqt/Utils/Base.h"
#include "coreqt/Utils/Singleton.h"

#include <QJSEngine>


class Script : public QObject, public Singleton<Script> {
Q_OBJECT

public:

	void init();

	void evaluate(QString& src);

	void reset();

public slots: 
	void out(QString text);

signals:
	void onOut(QString& text);

protected:
	QJSEngine* engine;
};


#endif

