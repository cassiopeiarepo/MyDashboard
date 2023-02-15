#ifndef __NODE_PROPTEST_H__
#define __NODE_PROPTEST_H__

#include "app/Nodes/NodeBase.h"

#include <QDateTime>

class NodePropTest : public NodeBase {
    Q_OBJECT
public:

    Q_PROPERTY(QString StringProp READ getString WRITE setString)
    Q_PROPERTY(int IntProp READ getInt WRITE setInt)
    Q_PROPERTY(float FloatProp READ getFloat WRITE setFloat)
    Q_PROPERTY(double DoubleProp READ getDouble WRITE setDouble)
    Q_PROPERTY(bool BoolProp READ getBool WRITE setBool)
    Q_PROPERTY(QDateTime DateTimeProp READ getDateTime WRITE setDateTime)
    Q_PROPERTY(QTime TimeProp READ getTime WRITE setTime)
    Q_PROPERTY(QDate DateProp READ getDate WRITE setDate)


    Q_PROPERTY(int IntProp2 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp3 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp4 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp5 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp6 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp7 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp8 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp9 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp10 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp11 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp12 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp13 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp14 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp15 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp16 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp17 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp18 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp19 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp20 READ getInt WRITE setInt)

    Q_PROPERTY(int IntProp21 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp22 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp23 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp24 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp25 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp26 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp27 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp28 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp29 READ getInt WRITE setInt)
    Q_PROPERTY(int IntProp30 READ getInt WRITE setInt)

    virtual void LoadTml(TmlNode* node);

    virtual QString getClassName() { return "propTest"; }

private:
    QString p_string;
    int p_int;
    float p_float;
    double p_double;
    bool p_bool;
    QDateTime p_datetime;
    QDate p_date;
    QTime p_time;

    QString getString() { return p_string;}
    void setString(const QString& str) { p_string = str;}

    int getInt() { return p_int;}
    void setInt(int val) { p_int = val; }

    float getFloat() { return p_float;}
    void setFloat(float val) { p_float = val; }

    double getDouble() { return p_double;}
    void setDouble(double val) { p_double = val; }

    bool getBool() { return p_bool;}
    void setBool(bool val) { p_bool = val; }

    QDateTime getDateTime() { return p_datetime;}
    void setDateTime(const QDateTime& val) { p_datetime = val; }

    QTime getTime() { return p_time;}
    void setTime(const QTime& val) { p_time = val; }

    QDate getDate() { return p_date;}
    void setDate(const QDate& val) { p_date = val; }


};

#endif /* __NODE_PROPTEST_H__ */
