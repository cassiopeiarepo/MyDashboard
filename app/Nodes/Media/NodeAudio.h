#ifndef __NODE_AUDIO_H__
#define __NODE_AUDIO_H__

#include "app/Nodes/NodeBase.h"


class NodeAudio : public NodeBase {
    Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

    virtual QString getClassName() { return "audio"; }

    void setPath(const QString& _path) { path = _path;}
    const QString getPath() { return path;}

private:
    QString path;
};

#endif /* __NODE_AUDIO_H__ */
