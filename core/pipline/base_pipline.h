#ifndef BASEPIPLINE_H
#define BASEPIPLINE_H

#include <core/chart_object.h>
#include <entity/dataentity.h>

#include <QObject>
#include <QVector>

class BasePipline : public ChartObject {
 public:
  BasePipline(QString piplineName = "Base", QObject* parent = nullptr);

 protected:
  /**
   * @brief currDataFlow 当前的数据流
   */
  QVector<DataEntity*>* currDataFlow = nullptr;

 protected:
  /**
   * @brief deleteAndFreeDataEntities 删除容器和释放内部元素内存引用
   * @param vector QVector&lt;DataEntity\*&gt;\*
   */
  void deleteAndFreeDataFlow();

 public:
  /**
   * @brief getCurrDataFlow 获得当前的数据流
   * @return QVector&lt;DataEntity\*&gt;\*
   */
  QVector<DataEntity*>* getCurrDataFlow() const;
};

#endif  // BASEPIPLINE_H
