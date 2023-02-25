#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "coreqt/Utils/Base.h"
#include "coreqt/Utils/Singleton.h"
#include "app/Utils/Log.h"

#include <QtGlobal>
#include <QString>
#include <QList>
#include <QMap>

class TypeDef {
public:
    TypeDef(const QString& typeName) : type_name(typeName) { }

    const QString& getTypeName() const { return type_name; }
    const QString& getCategory() const { return category; }
    const QString& getTmlName() const { return tml_name; }
    const QString& getIconRes() const { return icon_res; }

    void setCategory(const QString& _category) { category = _category; }
    void setTmlName(const QString& _tml_name) { tml_name = _tml_name; }
    void setIconRes(const QString& _icon_res) { icon_res = _icon_res; }

private:
	QString type_name;
    QString category;
	QString tml_name;
    QString icon_res;

    //friend class TypeSystem;
};

class TypeSystem : public Singleton<TypeSystem> {
public:

	void init();

    const QMetaObject* getMetaObjectByTypename(const QString& typeName);

    const TypeDef* getType(QString typeName);

    const QList<const TypeDef*>& getTypes() { return types; }
	const QMap<QString, QString>& getTmlNameMap() { return tml_name_map;  }

    QWidget* createWidgetForSceneView(const QString& mata_type_name);

    const QList<QString> getCategoryList() { return category_list; }

private:
    QList<const TypeDef*> types;
	QMap<QString, QString> tml_name_map;

    QList<QString> category_list;

    TypeDef* registerNodeType(QMetaObject metaObject);
    void build();

};

class TypeSystemUtils {
    //QList<TypeDef*> getDerivedTypes(TypeDef* parent_type) { }
};


#endif /* __TYPEDEF_H__ */
