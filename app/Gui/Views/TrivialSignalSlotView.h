#ifndef TRIVIAL_SIGNALSLOT_VIEW_H
#define TRIVIAL_SIGNALSLOT_VIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <QMetaMethod>

class TestObject1 : public QObject
{
    Q_OBJECT

public:

public slots:
    void start() { }
    void stop() { }

signals:
   void OnStart();
   void OnStop();
};


class TestTimer : public QObject {
Q_OBJECT
public:
    TestTimer() {
        timer = new QTimer();
        timer->setInterval(1000);
        QObject::connect(timer, &QTimer::timeout, this, &TestTimer::onTimer);
        timer->start();
    }

signals:
    void Interval();

private slots:
    void onTimer() {
        emit Interval();
        timer->start();
    }

private:
    QTimer* timer;
};

class TestLog : public QObject {
Q_OBJECT
public:
    TestLog() :counter(0) { }

public slots:
    void printlog() {
        qDebug() << "TestLog " << counter;
        counter++;
    }

private:
    int counter;
};

class TrivialSignalSlotView;

class TSSBaseItem : public QGraphicsItem {

public:
    /*
    virtual void mouseDoubleClickEvent(QMouseEvent* event) { };
    virtual void mouseMoveEvent(QMouseEvent* event)  { }
    virtual void mousePressEvent(QMouseEvent* event)  { }
    virtual void mouseReleaseEvent(QMouseEvent* event) { }

    virtual void keyPressEvent(QKeyEvent* event) { }
    virtual void keyReleaseEvent(QKeyEvent* event) {}
    */
protected:
    TrivialSignalSlotView* getView();
};

class TSSQObjectConnection {
public:
    TSSQObjectConnection(QObject* _sender, const QString& _signalSignature, QObject* _receiver,  const QString& _slotSignature) :
        sender(_sender), signalSignature(_signalSignature), receiver(_receiver), slotSignature(_slotSignature)
    {

    }

    QObject* getSender() { return sender; }
    QObject* getReceiver() { return receiver; }

    const QString& getSignalSignature() { return signalSignature; }
    const QString& getSlotSignature() { return slotSignature; }

    QPointF getMiddlePos() { return middlePos; }
    void setMiddlePos(QPointF _middlePos) { middlePos = _middlePos; }

private:
    QObject* sender;
    QObject* receiver;
    QString signalSignature;
    QString slotSignature;

    QPointF middlePos;

};

class TSSQObjectItem {
public:
    TSSQObjectItem(QObject* _obj) : obj(_obj){ }

    QObject* getObject() { return obj; }

    QPointF getPos() { return pos; }
    void setPos(QPointF _pos) { pos = _pos; }

private:
    QObject* obj;
    QPointF pos;
};

class TSSBoard {
public:

    const QList<TSSQObjectItem*>& getObjects() const { return objects; }
    const QList<TSSQObjectConnection*>& GetConnections() const { return connections; }

    void appandObject(TSSQObjectItem* obj) { objects.append(obj); }
    void appendConnection(TSSQObjectConnection* conn) { connections.append(conn); }

private:
    QList<TSSQObjectItem*> objects;
    QList<TSSQObjectConnection*> connections;
};

class TSSObjectItemGraph : public TSSBaseItem {
public:
    TSSObjectItemGraph() { }
    TSSObjectItemGraph(TSSQObjectItem* _obj_item) : obj_item(_obj_item), slotSize(10), margins(4) {
        text_font = new QFont("Arial", 10);
        text_font_matrics = new QFontMetrics(*text_font);
        //setFlag(ItemIsMovable, true);

    }

    ~TSSObjectItemGraph() {
        if (text_font_matrics) delete text_font_matrics;
        if (text_font) delete text_font;
    }

    QRectF boundingRect() const override { return QRectF(0, 0, width, height); }
    QPainterPath shape() const override {
        QPainterPath path;
        path.addRect(0, 0, width, height);
        return path;
    }

    TSSQObjectItem* getObjectItem() { return obj_item;}

    void setSlotList(QStringList& _slots) {
        obj_slots = _slots;
        updateSize();
    }

    void setSignalList(QStringList& _signals) {
        obj_signals = _signals;
        updateSize();
    }

    QPointF getSlotPoint(const QString& slotSignature) {
        QPointF result;

        result.setX(margins  + slotSize/2);

        int pos = obj_slots.indexOf(slotSignature);

        result.setY(margins + getLineHeight() *(1 + pos) + slotSize/2);

        return mapToScene(result);
    }

    QPointF getSignalPoint(const QString& signalSignature) {
        QPointF result;

        result.setX(width /*- margins - slotSize/2*/);
        int pos = obj_signals.indexOf(signalSignature);
        result.setY(margins + getLineHeight() *(1 + pos) + slotSize/2);

        QPointF result2 = mapToScene(result);

        return result2;
    }

    void updateGeom() {
        updateSize();
    }

protected:
    void updateSize() {
        QString obj_name = obj_item->getObject()->objectName();
        if (obj_name == "")
            obj_name = "Unknown";

        setPos(obj_item->getPos());

        int max_sig_slot_width = 0;

        for (QString str : obj_signals) {
            int width = getTextWidth(str);
            if (width > max_sig_slot_width)
                max_sig_slot_width = width;
        }

        for (QString str : obj_slots) {
            int width = getTextWidth(str);
            if (width > max_sig_slot_width)
                max_sig_slot_width = width;
        }

        width = 6* margins + 2 * slotSize + max_sig_slot_width*2;

        int obj_name_width = getTextWidth(obj_name);

        int width2 = margins * 4 + slotSize * 2 + obj_name_width;

        if (width2 > width) {
            width = width2;
        }

        int sig_slots = obj_signals.size();

        if (obj_slots.size() > sig_slots )
            sig_slots = obj_slots.size();

        height = getLineHeight() * (1 + sig_slots) + 2*margins;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

    int getTextWidth(QString& text)
    {
        return text_font_matrics->horizontalAdvance(text);
    }

    int getLineHeight() {
        return text_font_matrics->height();//text_font_matrics->lineSpacing();
    }


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override ;

    int width;
    int height;
    int slotSize;
    int margins;

    //QObject* obj;
    TSSQObjectItem* obj_item;
    QFont* text_font;
    QFontMetrics* text_font_matrics;
    QStringList obj_slots;
    QStringList obj_signals;

    QPointF m_dragStartPosition;

};

class TSSConnectionItemGraph : public TSSBaseItem {
public:
    TSSConnectionItemGraph() { }
    TSSConnectionItemGraph(TSSQObjectConnection* _conn) :
        conn(_conn) {

        //updateSize();
    }

    ~TSSConnectionItemGraph() {

    }

    /*
    prostokąt który zawiera signalPoint, slotPoint, middlePoint
    */

    QRectF boundingRect() const override { return QRectF(0, 0, width, height); }

    // linie laczace signalPoint, slotPoint, middlePoint
    QPainterPath shape() const override {
        QPainterPath path;
        //path.addRect(0, 0, width, height);

        path.moveTo(fromPoint);
        path.lineTo(QPointF(centralPoint.x(), fromPoint.y()));
        path.moveTo(QPointF(centralPoint.x(), fromPoint.y()));
        path.lineTo(QPointF(centralPoint.x(), toPoint.y()));
        path.moveTo(QPointF(centralPoint.x(), toPoint.y()));
        path.lineTo(toPoint);

        // Utwórz QPen z szerokością i oblicz margines obszaru kolizji
        qreal penWidth = 3;

        // Rozszerz obszar kolizji o margines, uwzględniając szerokość pióra
        QPainterPathStroker stroker;
        stroker.setWidth(penWidth);

        QPainterPath strokePath = stroker.createStroke(path);

        // Połącz ścieżki, aby uzyskać obszar kolizji z uwzględnieniem szerokości pióra
        path.addPath(strokePath);

        return path;
    }

    void updateGeom() {
        updateSize();
    }

    TSSQObjectConnection* getConn() { return conn; }


protected:
    void updateSize();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;

    //QPointF topLeft;
    //QPointF bottomRight;

    QPointF centralPoint;
    QPointF fromPoint;
    QPointF toPoint;

    int width;
    int height;

    TSSQObjectConnection* conn;
};


class TrivialSignalSlotView : public QGraphicsView {
    Q_OBJECT
public:
    TrivialSignalSlotView() : selected(NULL) {
        scene = new QGraphicsScene();
        this->setScene(scene);

        scene->setSceneRect(QRectF(0, 0, 10000, 10000));

        init();
    }

    void init() {
        //QObject* test1 = new TestObject1();

        TestTimer* testTimer = new TestTimer();
        testTimer->setObjectName("Timer1");

        TestLog* testLog = new TestLog();
        testLog->setObjectName("Log1");

        board = new TSSBoard();

        TSSQObjectItem* tss_object1 = new TSSQObjectItem(testTimer);
        tss_object1->setPos(QPointF(50, 50));
        board->appandObject(tss_object1);

        TSSQObjectItem* tss_object2 = new TSSQObjectItem(testLog);
        tss_object2->setPos(QPointF(550, 150));
        board->appandObject(tss_object2);

        TSSQObjectConnection* tss_conn1 = new TSSQObjectConnection(testTimer, "Interval()", testLog, "printlog()");
        tss_conn1->setMiddlePos(QPointF(350, 150));
        board->appendConnection(tss_conn1);

        connectSignals();
        updateScene();

        /*
        qDebug() << "--- Print Signals";
        printSignals(testTimer);
        qDebug() << "--- Print Slots";
        printSlot(testLog);

        test1->setObjectName("Timer1");
        TSSObjectItemGraph* item1 = new TSSObjectItemGraph(test1);
        scene->addItem(item1);
        item1->setPos(100, 100);
        */
    }

    void connectSignals() {
        for (TSSQObjectConnection* tss_conn : board->GetConnections()) {
            connectSignal(tss_conn);
        }
    }

    void connectSignal(TSSQObjectConnection* tss_conn) {
        const QMetaObject* metaObj = tss_conn->getSender()->metaObject();
        int signalIdx = metaObj->indexOfSignal(tss_conn->getSignalSignature().toStdString().c_str());
        QMetaMethod signal = metaObj->method(signalIdx);

        const QMetaObject* metaObj2 = tss_conn->getReceiver()->metaObject();
        int slotIdx = metaObj2->indexOfSlot(tss_conn->getSlotSignature().toStdString().c_str());
        QMetaMethod slot = metaObj2->method(slotIdx);

        bool ok = QObject::connect(tss_conn->getSender(), signal, tss_conn->getReceiver(), slot);

        if (!ok) {
            qFatal(" Failed to connect signal slot ");
        }
    }

    void updateScene() {
        scene->clear();

        for (TSSQObjectItem* tss_object : board->getObjects()) {
            TSSObjectItemGraph* item1 = new TSSObjectItemGraph(tss_object);
            scene->addItem(item1);
            objectItems.append(item1);
        }

        for (TSSQObjectConnection* tss_conn : board->GetConnections()) {
            TSSConnectionItemGraph* conn = new TSSConnectionItemGraph(tss_conn);
            scene->addItem(conn);
            connItems.append(conn);
        }

        updateObjectItemsGraphSignalSlot();

        for (TSSObjectItemGraph* item1 : objectItems) {
            item1->updateGeom();
            //item1->update();
        }

        for (TSSConnectionItemGraph* conn1 : connItems) {
            conn1->updateGeom();
            //conn1->update();
        }

    }

    void updateObjectItemsGraphSignalSlot() {
        for (TSSObjectItemGraph* item : objectItems) {
            updateObjectItemGraphSignalSlot(item);
        }
    }

    void updateObjectItemGraphSignalSlot(TSSObjectItemGraph* item1) {
        QStringList signalList;
        QStringList slotList;

        QObject* obj = item1->getObjectItem()->getObject();

        for (TSSQObjectConnection* conn :  board->GetConnections()) {
            if (conn->getSender() == obj) {
                signalList.append(conn->getSignalSignature());
            }

            if (conn->getReceiver() == obj) {
                slotList.append(conn->getSlotSignature());
            }
        }

        item1->setSignalList(signalList);
        item1->setSlotList(slotList);
    }

    void updateAllConnections(TSSObjectItemGraph* obj_item) {
        QObject* obj = obj_item->getObjectItem()->getObject();


        for (TSSConnectionItemGraph* conn_item : connItems) {
            TSSQObjectConnection* conn = conn_item->getConn();
            if (conn->getSender() == obj || conn->getReceiver() == obj) {
                //qDebug() << "update connection";
                conn_item->updateGeom();
                //conn_item->update();
            }
        }

        scene->update();
    }

    void printSignals(QObject* obj) {
        const QMetaObject *metaObject = obj->metaObject();
        int methodCount = metaObject->methodCount();

        for (int i = 0; i < methodCount; ++i) {
            QMetaMethod method = metaObject->method(i);
            if (method.methodType() == QMetaMethod::Signal) {
                qDebug() << "SignalSignature: " << method.methodSignature();
                //qDebug() << "SignalName: " << method.name();
            }
        }
    }

    void printSlot(QObject* obj) {
        const QMetaObject *metaObject = obj->metaObject();
        int methodCount = metaObject->methodCount();

        for (int i = 0; i < methodCount; ++i) {
            QMetaMethod method = metaObject->method(i);
            if (method.methodType() == QMetaMethod::Slot) {
                qDebug() << "Slot: " << method.methodSignature();
            }
        }
    }

    TSSObjectItemGraph* getObjectItemGraph(QObject* obj) {
        for (TSSObjectItemGraph* obj_item_graph : objectItems) {
            if (obj_item_graph->getObjectItem()->getObject() == obj)
                return obj_item_graph;
        }
        return NULL;
    }

    void setSelected(QGraphicsItem* sel) {
        if (sel == selected) return;

        QGraphicsItem* prev_sel = selected;

        selected = sel;

        if (selected) {
            selected->update();
        }

        if (prev_sel) {
            prev_sel->update();
        }

    }

    QGraphicsItem* getSelected() { return selected; }

private:
    QGraphicsScene* scene;
    QObject* test1;
    TSSBoard* board;
    QList<TSSObjectItemGraph*> objectItems;
    QList<TSSConnectionItemGraph*> connItems;

    QGraphicsItem* selected;

};

#endif
