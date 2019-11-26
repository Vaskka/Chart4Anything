#ifndef INTEGRALPIPLINE_H
#define INTEGRALPIPLINE_H

#include <core/pipline/base_pipline.h>
#include <entity/dataentity.h>

#include <QList>
#include <QObject>

/**
 * @brief The IntegralPipline class  处理积分的pipline
 */
class IntegralPipline : public BasePipline {
  Q_OBJECT

 signals:
  void afterIntegral(QString moduleName, QVector<DataEntity*>& list);

 public:
  IntegralPipline(QString moduleName, QObject* parent = nullptr);

 public slots:
  void processOriginalData(QVector<DataEntity*>& list);
};

#endif  // INTEGRALPIPLINE_H
