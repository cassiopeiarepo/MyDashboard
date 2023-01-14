#ifndef __NODE_UI_H__
#define __NODE_UI_H__

#include "core/types/Base.h"
#include "core/utils/Singleton.h"

#include <QString>
#include <QDateTime>
#include "app/Nodes/NodeBase.h"


/*
class Ui : public Singleton<Ui> {

};
*/



class NodeUi : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "ui"; }

private:

};


#endif /* __NODE_UI_H__ */
