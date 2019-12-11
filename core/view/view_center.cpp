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

  this->chartRef->addSeries(lineSeries);
  qint64 minX = lineSeries->at(0).x();
  qint64 maxX = lineSeries->at(lineSeries->count() - 1).x();

  qDebug() << "minX:" << minX;
  qDebug() << "maxX:" << maxX;

  this->chartRef->createDefaultAxes();
  this->chartRef->axisX()->setRange(minX, maxX);
}

void ViewCenter::removeFlowWithLineSeries(QLineSeries* lineSeries) {
  if (lineSeries == nullptr) {
    return;
  }

  this->chartRef->removeSeries(lineSeries);
}
