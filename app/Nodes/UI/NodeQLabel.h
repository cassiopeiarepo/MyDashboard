#ifndef __NODE_QLABEL_H__
#define __NODE_QLABEL_H__

#include "app/Nodes/UI/NodeQWidget.h"

#include <QLabel>

class NodeQLabel : public NodeQWidget {
	Q_OBJECT
public:

	NodeQLabel();

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "qlabel"; }

	QLabel* getLabel() { return label; }

protected:
	QLabel* label;

};


#endif /* __NODE_QLABEL_H__ */
