#ifndef DIFFERENTIALPIPLINE_H
#define DIFFERENTIALPIPLINE_H

#include <core/chart_object.h>
#include <entity/dataentity.h>

#include <QList>
#include <QObject>

/**
 * @brief The DifferentialPipline class  处理微分的pipline
 */
class DifferentialPipline : public ChartObject {
  Q_OBJECT

 private:
  QVector<DataEntity*>* currDataFlow = nullptr;

 signals:
  void afterDifferential(QString moduleName, QVector<DataEntity*>& list);

 public:
  DifferentialPipline(QObject* parent);

  QVector<DataEntity*>* getCurrDataFlow() const;

 public slots:
  void processOriginalData(QVector<DataEntity*>& list);
};

#endif  // DIFFERENTIALPIPLINE_H
