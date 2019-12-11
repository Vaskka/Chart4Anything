#ifndef CHART_4_ANYTHING_H
#define CHART_4_ANYTHING_H

#include <core/common.h>
#include <core/controller/data_manager.h>
#include <core/pipline/differential_pipline.h>
#include <core/pipline/integral_pipline.h>
#include <core/pipline/original_pipline.h>
#include <core/view/differential_view.h>
#include <core/view/integral_view.h>
#include <core/view/original_view.h>

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

  /**
   * @brief controller 控制层
   */
  DataManager* controller;

  /**
   * @brief viewCenter 原始视图层
   */
  OriginalView* originalView;

  /**
   * @brief differentialView 微分视图层
   */
  DifferentialView* differentialView;

  /**
   * @brief integralView 积分视图层
   */
  IntegralView* integralView;

  /**
   * @brief currentFilePath 当前展示的文件路径
   */
  QString currentFilePath;

 public:
  explicit Chart4Anything(QChart* originalChartRef,
                          QChart* differentialChartRef,
                          QChart* integralChartRef,
                          QObject* parent);

  /**
   * @brief processDataFlow 指定文件路径 并处理成各个通道的结果
   * @param path 文件路径
   */
  void processDataFlow(QString path, qint64 offset, qint64 length);

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
   * @brief resetOffset
   * 重置信号偏移，当前数据释放，重新从文件的offset读取length个data，并传递给对应通道处理
   * @param offset 偏移量
   * @param length 长度
   */
  void resetOffset(qint64 offset, qint64 length);

  /**
   * @brief drawOriginalChannal 绘制原始通道
   */
  void drawOriginalChannal();

  /**
   * @brief drawDifferentialChannel 绘制微分通道
   */
  void drawDifferentialChannel();

  /**
   * @brief drawIntegralChannel 绘制积分通道
   */
  void drawIntegralChannel();

  /**
   * @brief removeOriginChannel 移除原始通道图像
   */
  void removeOriginChannel();

  /**
   * @brief removeDifferentialChannel 移除微分通道图像
   */
  void removeDifferentialChannel();

  /**
   * @brief removeIntegralChannel 移除积分通道图像
   */
  void removeIntegralChannel();

  /**
   * @brief getCurrentOriginalChartRef 当前chart的引用
   * @return
   */
  QChart* getCurrentOriginalChartRef() const;

  /**
   * @brief getCurrentDifferentialChartRef 获得微分的chart引用
   * @return
   */
  QChart* getCurrentDifferentialChartRef() const;

  /**
   * @brief getCurrentIntegralChartRef 获得积分的chart引用
   * @return
   */
  QChart* getCurrentIntegralChartRef() const;

  /**
   * @brief getDataMapping 获取数据视图mapping
   * @return QMap
   */
  QMap<QString, QLineSeries*> getDataLineSeriesMapping() const;

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

  /**
   * @brief dealMappingDone 处理数据视图映射完成回调
   * @param channelName 通道名称
   * @param currentMapping currentMapping
   */
  void dealMappingDone(QString channelName,
                       QMap<QString, QLineSeries*>& currentMapping);
};

#endif  // CHART4ANYTHING_H
