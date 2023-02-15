#ifndef TRIVIALQUERYWIDGET_H
#define TRIVIALQUERYWIDGET_H

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QList>

class QueryItem;


void addChildWidgetAndFillInGrid(QWidget* parent, QWidget* child);


class Query : public QObject {
    Q_OBJECT
public:

    void addQueryItem(QueryItem* item) {
        items.append(item);
    }

private:
    QList<QueryItem*> items;
};

class QueryItem : public QObject {
    Q_OBJECT
public:
    QueryItem(Query* query) {
        setParent(query);
    }

};

class TrivaialQueryItemWidget : public QWidget {
    Q_OBJECT
public:
    TrivaialQueryItemWidget(QWidget *parent = nullptr);

 private:
    void createWidget();



    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *label;
    QLineEdit *lineEdit;
};



class TrivialQueryWidget : public QWidget
{
    Q_OBJECT
public:
    TrivialQueryWidget(QWidget *parent = nullptr);

    void addItem();


public slots:
    void onAddPressed();

signals:


private:
    void createWidget(QWidget* parent);

    void removeWidgets();
    void addWidgets();

    QList<TrivaialQueryItemWidget*> items;

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton;

};

#endif // TRIVIALQUERYWIDGET_H
