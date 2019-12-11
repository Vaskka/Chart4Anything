#include "integral_pipline.h"

IntegralPipline::IntegralPipline(QString moduleName, QObject* parent)
    : BasePipline(moduleName, parent) {}

void IntegralPipline::processOriginalData(QVector<DataEntity*>& list) {
  // 新数据到达释放原数据空间
  this->deleteAndFreeDataFlow();

  this->currDataFlow = new QVector<DataEntity*>;

  for (qint32 i = 0; i < list.length() - 1; i++) {
    DataEntity* currDataEntity = list.at(i);
    DataEntity* nextDataEntity = list.at(i + 1);

    qint16 integralValue =
        (currDataEntity->getValue() + nextDataEntity->getValue()) / 2;

    DataEntity* integralDataEntity =
        new DataEntity(currDataEntity->getNo(), integralValue);
    this->currDataFlow->append(integralDataEntity);
  }

  emit this->afterIntegral(this->getModuleName(), *this->currDataFlow);
}
