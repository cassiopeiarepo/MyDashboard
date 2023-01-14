#ifndef TRIVIAL_SCRIPT_VIEW_H
#define TRIVIAL_SCRIPT_VIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QSplitter>

class TrivialScriptView : public QWidget {
Q_OBJECT

public:
	TrivialScriptView();

protected:
	void resizeEvent(QResizeEvent* event) override;


	protected slots:
		void onWidgetIntextChanged();
		void onOut(QString& txt);
protected:
	QTextEdit* widget_out;
	QTextEdit* widget_in;
	QSplitter* spliter1;
};


#endif
