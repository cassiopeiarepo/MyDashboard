#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "core/types/Base.h"
#include "core/utils/Singleton.h"
#include "app/Utils/Log.h"


#include <QString>
#include <QList>
#include <QMap>

class TypeDef {
public:
	const QString& getTypeName() { return type_name; }
	const QString& getTmlName() { return tml_name; }

private:
	QString type_name;
	QString tml_name;

	friend class TypeSystem;
};

class TypeSystem : public Singleton<TypeSystem> {
public:

	void init();

	TypeDef* getType(QString typeName);

	const QList<TypeDef*>& getTypes() { return types; }
	const QMap<QString, QString>& getTmlNameMap() { return tml_name_map;  }

	QList<TypeDef*> getDerivedTypes(TypeDef* parent_type) { }
	

private:
	QList<TypeDef*> types;
	QMap<QString, QString> tml_name_map;

	TypeDef* registerType(QMetaObject metaObject);

};

#endif /* __TYPEDEF_H__ */
