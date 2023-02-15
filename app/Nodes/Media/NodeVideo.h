#ifndef __NODE_VIDEO_H__
#define __NODE_VIDEO_H__

#include "app/Nodes/NodeBase.h"


class NodeVideo : public NodeBase {
    Q_OBJECT
public:

    virtual void LoadTml(TmlNode* node);

    virtual QString getClassName() { return "video"; }

    void setPath(const QString& _path) { path = _path;}
    const QString getPath() { return path;}

private:
    QString path;
};

#endif /* __NODE_VIDEO_H__ */
