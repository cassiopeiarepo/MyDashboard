#include "app/Utils/TypeDef.h"

#include "app/Nodes/NodeBase.h"
#include "app/Nodes/NodeInclude.h"
#include "app/Nodes/NodeVar.h"
#include "app/Nodes/Pim/NodeEvent.h"
#include "app/Nodes/Pim/NodePerson.h"
#include "app/Nodes/Pim/NodeProject.h"
#include "app/Nodes/Pim/NodeTask.h"

#include "app/Nodes/Basic/NodeText.h"
#include "app/Nodes/Basic/NodeHeading1.h"
#include "app/Nodes/Basic/NodeHeading2.h"
#include "app/Nodes/Basic/NodeHeading3.h"
#include "app/Nodes/Basic/NodeLink.h"

#include "app/Gui/SceneWidgets/TrivialSceneNodeTextWidget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeLinkWidget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeHeading1Widget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeHeading2Widget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeHeading3Widget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeImageWidget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeVideoWidget.h"
#include "app/Gui/SceneWidgets/TrivialSceneNodeAudioWidget.h"

void TypeSystem::init() {

    TypeDef* type_def = NULL;

    //type_def = registerNodeType(NodeBase::staticMetaObject);
        type_def = registerNodeType(NodeDummy::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("dummy");
            type_def->setIconRes(":/icons/ui/icons/crop_square_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeDummy>();

        type_def = registerNodeType(NodeInclude::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("include");
            type_def->setIconRes(":/icons/ui/icons/note_add_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeInclude>();

        type_def = registerNodeType(NodeVar::staticMetaObject);

        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("var");
            type_def->setIconRes(":/icons/ui/icons/variables_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeVar>();

    // Pim
    type_def = registerNodeType(NodeEvent::staticMetaObject);
    type_def = registerNodeType(NodePerson::staticMetaObject);
    type_def = registerNodeType(NodeProject::staticMetaObject);
    type_def = registerNodeType(NodeTask::staticMetaObject);

    //Basic
        type_def = registerNodeType(NodeText::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("text");
            type_def->setIconRes(":/icons/ui/icons/article_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeText>();

        type_def = registerNodeType(NodeHeading1::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("heading1");
            type_def->setIconRes(":/icons/ui/icons/format_h1_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeHeading1>();

        type_def = registerNodeType(NodeHeading2::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("heading2");
            type_def->setIconRes(":/icons/ui/icons/format_h2_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeHeading2>();

        type_def = registerNodeType(NodeHeading3::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("heading3");
            type_def->setIconRes(":/icons/ui/icons/format_h3_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeHeading3>();

        type_def = registerNodeType(NodeLink::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Basic");
            type_def->setTmlName("link");
            type_def->setIconRes(":/icons/ui/icons/share_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeLink>();


    //Media
        type_def = registerNodeType(NodeAudio::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Media");
            type_def->setTmlName("audio");
            type_def->setIconRes(":/icons/ui/icons/music_note_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeAudio>();

        type_def = registerNodeType(NodeImage::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Media");
            type_def->setTmlName("image");
            type_def->setIconRes(":/icons/ui/icons/image_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeImage>();

        type_def = registerNodeType(NodeVideo::staticMetaObject);
        if (type_def) {
            type_def->setCategory("Media");
            type_def->setTmlName("video");
            type_def->setIconRes(":/icons/ui/icons/movie_FILL0_wght400_GRAD0_opsz48.png");
        }
        qRegisterMetaType<NodeVideo>();
	

    build();
}

void TypeSystem::build() {

    for (const TypeDef* typeDef : types) {
        if (typeDef->getTmlName() != "") {
            tml_name_map[typeDef->getTmlName()] = typeDef->getTypeName();
        } else {
            tml_name_map[typeDef->getTypeName()] = typeDef->getTypeName();
        }
    }


    //QList<const QString> myList;
    //QString txt = "test1";
    //myList.append(txt);

    //myList.append(QStringLiteral("hello"));
    //myList.append(QStringLiteral("world"));
/*
    for (const TypeDef* typeDef : types) {
        if (!myList.contains(typeDef->getCategory())) {
            myList.append(typeDef->getCategory());
        }
    }
*/
}

const QMetaObject* TypeSystem::getMetaObjectByTypename(const QString& typeName) {
    QMetaType mt = QMetaType::fromName(QByteArrayView(typeName.toUtf8()));

    if (!mt.isValid())
        return NULL;

    return mt.metaObject();
}

const TypeDef* TypeSystem::getType(QString typeName) {
    for (const TypeDef* typeDef : types) {
        if (typeDef->getTypeName() == typeName) {
			return typeDef;
		}
	}
	return NULL;
}

TypeDef* TypeSystem::registerNodeType(QMetaObject metaObject) {

	QMetaType metaType = metaObject.metaType();

    TypeDef* result = NULL;

	if (getType(metaType.name())) {
        qCritical() << "TypeSystem::registerNodeType type " << metaType.typeName << " already defined";
        return NULL;
	}

	if (!metaObject.inherits(&NodeBase::staticMetaObject)) {
        qCritical() << "TypeSystem::registerNodeType try to register type not inherited from NodeBase";
		return NULL;
	}

	const QMetaObject* parentMetaObject = metaObject.superClass();

    if (parentMetaObject->metaType().name() != QString("NodeBase")) {
        QMetaType parentMetaType = parentMetaObject->metaType();

        if (!getType(parentMetaType.name())) {
            qCritical() << "TypeSystem::registerNodeType parent class of " << metaType.typeName << " not defined";
            return NULL;
        }
    }

    result = new TypeDef(metaType.name());

    types.append(result);

    return result;
}

QWidget* TypeSystem::createWidgetForSceneView(const QString& mata_type_name) {
    QWidget* widget = NULL;

    qDebug() << "TypeSystem::createWidgetForSceneView create widget for " << mata_type_name;

    if (mata_type_name == "NodeText") {
        widget = new TrivialSceneNodeTextWidget();
    } else if (mata_type_name == "NodeLink") {
        widget = new TrivialSceneNodeLinkWidget();
    } else if (mata_type_name == "NodeHeading1") {
        widget = new TrivialSceneNodeHeading1Widget();
    } else if (mata_type_name == "NodeHeading2") {
        widget = new TrivialSceneNodeHeading2Widget();
    } else if (mata_type_name == "NodeHeading3") {
        widget = new TrivialSceneNodeHeading3Widget();
    } else if (mata_type_name == "NodeImage") {
        widget = new TrivialSceneNodeImageWidget();
    } else if (mata_type_name == "NodeVideo") {
        widget = new TrivialSceneNodeVideoWidget();
    } else if (mata_type_name == "NodeAudio") {
        widget = new TrivialSceneNodeAudioWidget();
    }

    return widget;
}



