#include "differential_pipline.h"

DifferentialPipline::DifferentialPipline(QString moduleName, QObject* parent)
    : BasePipline(moduleName, parent) {}

void DifferentialPipline::processOriginalData(QVector<DataEntity*>& list) {
  // 新数据到达释放原数据空间
  this->deleteAndFreeDataFlow();

  this->currDataFlow = new QVector<DataEntity*>;

  for (qint32 i = 0; i < list.length() - 1; i++) {
    DataEntity* currDataEntity = list.at(i);
    DataEntity* nextDataEntity = list.at(i + 1);

    qint16 diffValue = nextDataEntity->getValue() - currDataEntity->getValue();

    DataEntity* diffEntity = new DataEntity(i, diffValue);
    this->currDataFlow->append(diffEntity);
  }

  emit this->afterDifferential(this->getModuleName(), *this->currDataFlow);
}
