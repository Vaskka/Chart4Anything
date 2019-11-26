#include "view_center.h"

QChart* ViewCenter::getChartRef() const {
  return chartRef;
}

ViewCenter::ViewCenter(QChart* chartRef, QObject* parent)
    : ChartObject("ViewCenter", parent) {
  this->chartRef = chartRef;
}

/**
 * @brief drawDataFlow 向chart中绘制指定的数据
 * @param dataFlow 数据流
 */
void ViewCenter::drawDataFlow(QVector<DataEntity*>* dataFlow) {
  // 还没有数据 不更改Chart
  if (dataFlow == nullptr) {
    return;
  }

  QLineSeries* series = new QLineSeries();

  for (qint32 i = 0; i < dataFlow->length(); i++) {
    DataEntity* currDataEntity = dataFlow->at(i);
    series->append(currDataEntity->getNo(), currDataEntity->getValue());
  }

  this->chartRef->addSeries(series);
  this->chartRef->createDefaultAxes();
}
