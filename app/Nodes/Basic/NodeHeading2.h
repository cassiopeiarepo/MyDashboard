#ifndef __NODE_HEADING2_H__
#define __NODE_HEADING2_H__

#include "app/Nodes/NodeBase.h"


class NodeHeading2 : public NodeBase {
    Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

    virtual QString getClassName() { return "heading2"; }

    void setText(const QString& txt) { text = txt;}
    const QString getText() { return text;}

private:
    QString text;
};

#endif /* __NODE_HEADING2_H__ */
