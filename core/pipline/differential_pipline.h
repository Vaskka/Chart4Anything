#ifndef DIFFERENTIALPIPLINE_H
#define DIFFERENTIALPIPLINE_H

#include <core/pipline/base_pipline.h>
#include <entity/dataentity.h>

#include <QList>
#include <QObject>

/**
 * @brief The DifferentialPipline class  处理微分的pipline
 */
class DifferentialPipline : public BasePipline {
  Q_OBJECT

 signals:
  void afterDifferential(QString moduleName, QVector<DataEntity*>& list);

 public:
  DifferentialPipline(QString moduleName, QObject* parent = nullptr);

 public slots:
  void processOriginalData(QVector<DataEntity*>& list);
};

#endif  // DIFFERENTIALPIPLINE_H
