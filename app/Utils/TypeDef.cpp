#include "app/Utils/TypeDef.h"

#include "app/Nodes/NodeBase.h"
#include "app/Nodes/NodeInclude.h"
#include "app/Nodes/NodeVar.h"
#include "app/Nodes/Pim/NodeEvent.h"
#include "app/Nodes/Pim/NodePerson.h"
#include "app/Nodes/Pim/NodeProject.h"
#include "app/Nodes/Pim/NodeTask.h"


void TypeSystem::init() {

	TypeDef* type_def = registerType(NodeDummy::staticMetaObject);


	/*
	type_def = registerType<NodeDummy>();
	type_def->tml_name = "dummy";
	
	type_def = registerType<NodeInclude>();
	type_def->tml_name = "include";

	type_def = registerType<NodeVar>();
	type_def->tml_name = "var";

	type_def = registerType<NodeEvent>();
	type_def->tml_name = "event";

	type_def = registerType<NodePerson>();
	type_def->tml_name = "person";

	type_def = registerType<NodeProject>();
	type_def->tml_name = "project";

	type_def = registerType<NodeTask>();
	type_def->tml_name = "task";
	*/
	
}

TypeDef* TypeSystem::getType(QString typeName) {
	for (TypeDef* typeDef : types) {
		if (typeDef->type_name == typeName) {
			return typeDef;
		}
	}
	return NULL;
}

TypeDef* TypeSystem::registerType(QMetaObject metaObject) {

	QMetaType metaType = metaObject.metaType();

	if (getType(metaType.name())) {
		qCritical() << "TypeSystem::registerType type " << metaType.typeName << " already defined";
	}

	if (!metaObject.inherits(&NodeBase::staticMetaObject)) {
		qCritical() << "TypeSystem::registerType try to register type not inherited from NodeBase";
		return NULL;
	}

	const QMetaObject* parentMetaObject = metaObject.superClass();

	QMetaType parentMetaType = parentMetaObject->metaType();

	if (!getType(parentMetaType.name())) {
		qCritical() << "TypeSystem::registerType parent class of " << metaType.typeName << " not defined";
	}

	return NULL;
}


