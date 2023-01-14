#include "app/Gui/Views/TrivialScriptView.h"
#include "app/Utils/Script.h"


TrivialScriptView::TrivialScriptView() : QWidget() {

	spliter1 = new QSplitter(this);
	spliter1->setOrientation(Qt::Vertical);

	widget_out = new QTextEdit(this);
	widget_in = new QTextEdit(this);

	spliter1->addWidget(widget_out);
	spliter1->addWidget(widget_in);

	QObject::connect(Script::get(), &Script::onOut,
		this, &TrivialScriptView::onOut);

	QObject::connect(widget_in, &QTextEdit::textChanged,
		this, &TrivialScriptView::onWidgetIntextChanged);
	
}


void TrivialScriptView::resizeEvent(QResizeEvent* event) {
	spliter1->resize(width(), height());
	QWidget::resizeEvent(event);
}


void TrivialScriptView::onWidgetIntextChanged() {
	QString text = widget_in->toPlainText();
	int new_line_pos = text.indexOf('\n');
	if (new_line_pos >= 0) {
		QString line = text.left(new_line_pos);
		Script::get()->evaluate(line);
		widget_in->setPlainText("");
	}
}

void TrivialScriptView::onOut(QString& txt) {
	QString all_txt = widget_out->toPlainText();
	all_txt += txt;
	widget_out->setPlainText(all_txt);
}