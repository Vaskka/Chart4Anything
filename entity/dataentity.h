#ifndef DATAENTITY_H
#define DATAENTITY_H

#include <QObject>

class DataEntity
{
private:

    quint64 no;

    quint16 value;

public:
    DataEntity(quint64 no, quint16 value);
    quint16 getValue() const;
    void setValue(const quint16 &value);
    quint64 getNo() const;
    void setNo(const quint64 &no);
};

#endif // DATAENTITY_H
