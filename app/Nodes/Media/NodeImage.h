#ifndef __NODE_IMAGE_H__
#define __NODE_IMAGE_H__

#include "app/Nodes/NodeBase.h"


class NodeImage : public NodeBase {
    Q_OBJECT
public:

    virtual void LoadTml(TmlNode* node);

    virtual QString getClassName() { return "image"; }

    void setPath(const QString& _path) { path = _path;}
    const QString getPath() { return path;}

private:
    QString path;
};

#endif /* __NODE_IMAGE_H__ */
