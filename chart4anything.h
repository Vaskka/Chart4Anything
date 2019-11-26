#ifndef CHART_4_ANYTHING_H
#define CHART_4_ANYTHING_H

#include <core/chart_object.h>
#include <core/pipline/differential_pipline.h>
#include <core/pipline/integral_pipline.h>
#include <core/pipline/original_pipline.h>

#include <QObject>
#include <QVector>

class Chart4Anything : public ChartObject {
  Q_OBJECT
 private:
  /**
   * @brief originalPipline 原始通道
   */
  OriginalPipline* originalPipline;

  /**
   * @brief integralPipline 微分通道
   */
  IntegralPipline* integralPipline;

  /**
   * @brief differentialPipline 积分通道
   */
  DifferentialPipline* differentialPipline;

 public:
  explicit Chart4Anything(QObject* parent);

  /**
   * @brief processDataFlow 指定文件路径 并处理成各个通道的结果
   * @param path 文件路径
   */
  void processDataFlow(QString path);

  /**
   * @brief getCurrentOriginalFlow 获得当前原始通道的数据流
   * @return QVector&lt;DataEntity*&gt;\&
   */
  QVector<DataEntity*>& getCurrentOriginalFlow() const;

  /**
   * @brief getDifferentialFlow 获得当前微分通道的数据流
   * @return QVector&lt;DataEntity*&gt;\&
   */
  QVector<DataEntity*>& getDifferentialFlow() const;

  /**
   * @brief getIntegralFlow 获得当前积分通道的数据流
   * @return QVector&lt;DataEntity*&gt;\&
   */
  QVector<DataEntity*>& getIntegralFlow() const;

 private slots:

  /**
   * @brief dealReadDataDone 数据读入完成回调
   * @param fileName 文件名
   * @param fileLength 文件长度 (bytes-number)
   * @param fileContent (bytes-flow)
   */
  void dealReadDataDone(const QString fileName,
                        const qint32 fileLength,
                        QByteArray& fileContent);

  /**
   * @brief dealOriginalProcessDataDone 原始数据处理完成回调
   * @param fileName 文件名
   * @param dataEntityNumber  数据点个数
   * @param dataUnitList processed-data-flows
   */
  void dealOriginalProcessDataDone(const QString fileName,
                                   const qint32 dataEntityNumber,
                                   QVector<DataEntity*>& dataUnitList);

  /**
   * @brief dealExtraProcessDataDone 其他通道的处理完成回调
   * @param dataFlow processed-data-flows
   */
  void dealExtraProcessDataDone(QString moduleName,
                                QVector<DataEntity*>& dataFlow);

  /**
   * @brief dealCatchError 异常处理回调
   * @param exception ChartException 异常信息
   */
  void dealCatchError(ChartException& exception);
};

#endif  // CHART4ANYTHING_H
