#ifndef VIEWCENTER_H
#define VIEWCENTER_H

#include <core/chart_object.h>
#include <entity/dataentity.h>

#include <QObject>
#include <QVector>
#include <QtCharts>

class ViewCenter : public ChartObject {
 private:
  QChart* chartRef;

 public:
  ViewCenter(QString moduleName, QChart* chartRef, QObject* parent = nullptr);

  /**
   * @brief drawFlowWithLineSeries 绘制曲线
   * @param lineSeries
   */
  void drawFlowWithLineSeries(QLineSeries* lineSeries);

  /**
   * @brief removeFlowWithLineSeries 取消绘制
   * @param lineSeries
   */
  void removeFlowWithLineSeries(QLineSeries* lineSeries);

  /**
   * @brief getChartRef 内部QChart引用
   * @return
   */
  QChart* getChartRef() const;
};

#endif  // VIEWCENTER_H
