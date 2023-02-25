#ifndef __NODE_PANEL_H__
#define __NODE_PANEL_H__

#include "app/Nodes/NodeBase.h"

#include "app/Gui/Windows/TrivialMainWindow.h"

class NodePanel : public NodeBase {
	Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

	virtual QString getClassName() { return "panel"; }

private:
	QString name;
	TrivialMainWindow::PanelPlace place;

	bool StrToPanelPlace(const QString& str, TrivialMainWindow::PanelPlace* panel_place);

};

#endif /* __NODE_VAR_H__ */

