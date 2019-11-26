#ifndef CHART_4_ANYTHING_H
#define CHART_4_ANYTHING_H

#include <core/chart_object.h>
#include <core/pipline/differential_pipline.h>
#include <core/pipline/integral_pipline.h>
#include <core/pipline/original_pipline.h>
#include <core/view/view_center.h>

#include <QObject>
#include <QVector>

class Chart4Anything : public ChartObject {
  Q_OBJECT
 signals:
  /**
   * @brief allDataFlowReady 全部通道数据 准备完毕
   * @param piplineList QList&lt;BasePipline\*&sgt;
   */
  void allDataFlowReady(QList<BasePipline*> piplineList);

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

  /**
   * @brief viewCenter 视图中心
   */
  ViewCenter* viewCenter;

 public:
  explicit Chart4Anything(QChart* chartRef, QObject* parent);

  /**
   * @brief processDataFlow 指定文件路径 并处理成各个通道的结果
   * @param path 文件路径
   */
  void processDataFlow(QString path);

  /**
   * @brief getCurrentOriginalFlow 获得当前原始通道的数据流
   * @return QVector&lt;DataEntity*&gt;\&
   */
  QVector<DataEntity*>& getOriginalFlow() const;

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

  /**
   * @brief drawOriginalDataFlow 绘制原始通道波形
   */
  void drawOriginalDataFlow();

  /**
   * @brief drawDifferentialDataFlow 绘制微分通道波形
   */
  void drawDifferentialDataFlow();

  /**
   * @brief drawIntegralDataFlow 绘制积分通道波形
   */
  void drawIntegralDataFlow();

  /**
   * @brief getViewCenter 当前chart的引用
   * @return
   */
  QChart* getCurrentChartRef() const;

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
   * @brief Chart4Anything::dealExtraProcessDataDone
   * 处理其他通道解析完毕（after-original）
   * @param moduleName 模块名
   * @param dataFlow 数据流引用
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
