#ifndef __NODE_DOCUMENT_FILE_TYPE_H__
#define __NODE_DOCUMENT_FILE_TYPE_H__

#include "app/Nodes/NodeBase.h"


class NodeDocumentFileType : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "document_file_type"; }

private:
	QString name;
	QString ext; 
	QString type;
	QString subtype;
};

#endif /* __NODE_DOCUMENT_FILE_TYPE_H__ */