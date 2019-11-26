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
  ViewCenter(QChart* chartRef, QObject* parent = nullptr);

  /**
   * @brief drawDataFlow 向chart中绘制指定的数据
   * @param dataFlow 数据流
   */
  void drawDataFlow(QVector<DataEntity*>* dataFlow);

  /**
   * @brief getChartRef 内部QChart引用
   * @return
   */
  QChart* getChartRef() const;
};

#endif  // VIEWCENTER_H
