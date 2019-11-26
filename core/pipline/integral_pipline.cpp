#include "integral_pipline.h"

QVector<DataEntity*>* IntegralPipline::getCurrDataFlow() const {
  return currDataFlow;
}

IntegralPipline::IntegralPipline(QObject* parent)
    : ChartObject("IntegralPipline", parent) {}

void IntegralPipline::processOriginalData(QVector<DataEntity*>& list) {
  // 新数据到达释放原数据空间s
  if (this->currDataFlow != nullptr) {
    delete this->currDataFlow;
    this->currDataFlow = nullptr;
  }

  this->currDataFlow = new QVector<DataEntity*>;

  for (qint32 i = 0; i < list.length() - 1; i++) {
    DataEntity* currDataEntity = list.at(i);
    DataEntity* nextDataEntity = list.at(i + 1);

    qint16 integralValue =
        (currDataEntity->getValue() + nextDataEntity->getValue()) / 2;

    DataEntity* integralDataEntity = new DataEntity(i, integralValue);
    this->currDataFlow->append(integralDataEntity);
  }

  emit this->afterIntegral(this->getModuleName(), *this->currDataFlow);
}
