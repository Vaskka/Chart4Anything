#ifndef INTEGRALPIPLINE_H
#define INTEGRALPIPLINE_H

#include <core/chart_object.h>
#include <entity/dataentity.h>

#include <QList>
#include <QObject>

/**
 * @brief The IntegralPipline class  处理积分的pipline
 */
class IntegralPipline : public ChartObject {
  Q_OBJECT
 private:
  QVector<DataEntity*>* currDataFlow = nullptr;
 signals:
  void afterIntegral(QString moduleName, QVector<DataEntity*>& list);

 public:
  IntegralPipline(QObject* parent);

  QVector<DataEntity*>* getCurrDataFlow() const;

 public slots:
  void processOriginalData(QVector<DataEntity*>& list);
};

#endif  // INTEGRALPIPLINE_H
