#ifndef __WORKSPACE_H__
#define __WORKSPACE_H__

#include "core/types/Base.h"
#include "core/utils/Singleton.h"
#include "coreqt/Common/Tml.h"
#include "app/Nodes/NodeBase.h"

#include <QFileInfo>
#include <QMap>
#include <QDir>
#include <QList>

class NodeBase;
class TmlDef;

class InputFile {
public:
	QFileInfo file;
	TmlNode* root_node;
	TmlNode* current_node;
};


class Workspace : public Singleton<Workspace> {
public:

	void init(QString _dir);

	const QDir& getDir() { return dir; }

	void setVar(const QString& name, const QString& value);
	QString getVar(const QString& name);

	void setTmlDef(const QString& name, TmlDef* tml_def);
	TmlDef* getTmlDef(const QString& name);

	QList<InputFile*>& getInputFile() { return inputFiles; }
	InputFile* getTopInputFile() {  if (inputFiles.size() == 0) 
										return NULL; 
									else return inputFiles[inputFiles.size() - 1];  }

	const char* getCorrentInputFile();

	NodeBase* getRoot() { return root; }

	void pushInputFile(QString relative_file_path);
	void popInputFile();

	NodeBase* createNode(QString& name);

private:
	QDir dir;
	QMap<QString, QString> vars;
	QMap<QString, TmlDef*> tml_defs;
	
	NodeBase* root;
	QList<InputFile*> inputFiles;

	void loadDefaultFile(QString _dir);
	void loadTml(NodeBase* parent);

};


#endif /* __WORKSPACE_H__ */
