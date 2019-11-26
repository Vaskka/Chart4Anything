#include "dataentity.h"

DataEntity::DataEntity(qint32 no, qint16 value) {
  this->no = no;
  this->value = value;
}

qint16 DataEntity::getValue() const {
  return value;
}

void DataEntity::setValue(const qint16& value) {
  this->value = value;
}

qint32 DataEntity::getNo() const {
  return no;
}

void DataEntity::setNo(const qint32& no) {
  this->no = no;
}
