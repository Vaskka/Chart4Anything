#ifndef DATAENTITY_H
#define DATAENTITY_H

#include <QObject>

class DataEntity {
 private:
  qint32 no;

  qint16 value;

 public:
  DataEntity(qint32 no, qint16 value);
  qint16 getValue() const;
  void setValue(const qint16& value);
  qint32 getNo() const;
  void setNo(const qint32& no);
};

#endif  // DATAENTITY_H
