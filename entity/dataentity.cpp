#include "dataentity.h"

DataEntity::DataEntity(quint64 no, quint16 value)
{
    this->no = no;
    this->value = value;
}

quint16 DataEntity::getValue() const
{
    return value;
}

void DataEntity::setValue(const quint16 &value)
{
    this->value = value;
}

quint64 DataEntity::getNo() const
{
    return no;
}

void DataEntity::setNo(const quint64 &no)
{
    this->no = no;
}
