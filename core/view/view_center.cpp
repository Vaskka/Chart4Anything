#include "view_center.h"

QChart* ViewCenter::getChartRef() const {
  return chartRef;
}

ViewCenter::ViewCenter(QString moduleName, QChart* chartRef, QObject* parent)
    : ChartObject(moduleName, parent) {
  this->chartRef = chartRef;
}

void ViewCenter::drawFlowWithLineSeries(QLineSeries* lineSeries) {
  if (lineSeries == nullptr) {
    return;
  }

  qint64 minX = lineSeries->at(0).x();
  qint64 maxX = lineSeries->at(lineSeries->count() - 1).x();

  qDebug() << "===--===" << this->getModuleName();
  qDebug() << "minX:" << minX;
  qDebug() << "maxX:" << maxX;

  qint16 maxY = 0x7FFF;
  qint16 minY = 0x8000;
  this->chartRef->addSeries(lineSeries);
  this->chartRef->createDefaultAxes();

  // 定制水平轴
  QValueAxis* horizontalAxis = dynamic_cast<QValueAxis*>(
      this->chartRef->axes(Qt::Horizontal, lineSeries).back());
  horizontalAxis->setRange(minX, maxX);
  horizontalAxis->setGridLineVisible(true);
  horizontalAxis->setLabelFormat("%d");

  // 定制垂直轴
  QValueAxis* verticalAxis = dynamic_cast<QValueAxis*>(
      this->chartRef->axes(Qt::Vertical, lineSeries).back());
  verticalAxis->setRange(minY, maxY);
  verticalAxis->setGridLineVisible(true);
  verticalAxis->setLabelFormat("%d");
}

void ViewCenter::removeFlowWithLineSeries(QLineSeries* lineSeries) {
  if (lineSeries == nullptr) {
    return;
  }

  this->chartRef->removeSeries(lineSeries);
}
