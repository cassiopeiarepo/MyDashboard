#ifndef __NODE_HEADING3_H__
#define __NODE_HEADING3_H__

#include "app/Nodes/NodeBase.h"


class NodeHeading3 : public NodeBase {
    Q_OBJECT
public:

    virtual void LoadTml(TmlNode* node);

    virtual QString getClassName() { return "heading3"; }

    void setText(const QString& txt) { text = txt;}
    const QString getText() { return text;}

private:
    QString text;
};

#endif /* __NODE_HEADING3_H__ */
