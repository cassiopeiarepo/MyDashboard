#include "app/Utils/Script.h"
#include <QDebug>
#include "app/Utils/Log.h"

void Script::init() {
	engine = new QJSEngine();
	QJSValue script_obj = engine->newQObject(this);
	engine->setObjectOwnership(this, QJSEngine::CppOwnership);
	engine->globalObject().setProperty("Script", script_obj);

	script_obj = engine->newQObject(Log::get());
	engine->setObjectOwnership(this, QJSEngine::CppOwnership);
	engine->globalObject().setProperty("Log", script_obj);
}

void Script::evaluate(QString& src) {
	QJSValue result = engine->evaluate(src);
	if (result.isError()) {
		int line = result.property("lineNumber").toInt();
		qCritical() << "uncaught exception at line " << line << " : " << result.toString();
	}
}

void Script::out(QString text) {
	emit onOut(text);
}

void Script::reset() {
	if (engine) {
		delete engine;
		engine = NULL;
	}

	engine = new QJSEngine();
}

