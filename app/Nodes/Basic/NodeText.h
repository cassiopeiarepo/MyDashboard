#ifndef __NODE_TEXT_H__
#define __NODE_TEXT_H__

#include "app/Nodes/NodeBase.h"


class NodeText : public NodeBase {
	Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

	virtual QString getClassName() { return "text"; }

    void setText(const QString& txt) { text = txt;}
    const QString getText() { return text;}

private:
	QString text;
};

#endif /* __NODE_TEXT_H__ */
