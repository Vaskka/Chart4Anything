#include "chart4anything.h"

Chart4Anything::Chart4Anything(QChart* chartRef, QObject* parent)
    : ChartObject("Chart4Anything", parent) {
  this->originalPipline = new OriginalPipline("Original", this);
  this->integralPipline = new IntegralPipline("Integer", this);
  this->differentialPipline = new DifferentialPipline("Differential", this);
  this->viewCenter = new ViewCenter(chartRef, this);

  // 连接数据读入回调
  connect(this->originalPipline, &OriginalPipline::readDataDone, this,
          &Chart4Anything::dealReadDataDone);

  //  连接原始数据处理回调
  connect(this->originalPipline, &OriginalPipline::processDataDone, this,
          &Chart4Anything::dealOriginalProcessDataDone);

  // 连接异常处理回调
  connect(this->originalPipline, &OriginalPipline::catchError, this,
          &Chart4Anything::dealCatchError);

  // 连接其他通道处理完成回调
  connect(this->integralPipline, &IntegralPipline::afterIntegral, this,
          &Chart4Anything::dealExtraProcessDataDone);
  connect(this->differentialPipline, &DifferentialPipline::afterDifferential,
          this, &Chart4Anything::dealExtraProcessDataDone);
}

/**
 * @brief processDataFlow 指定文件路径 并处理成各个通道的结果
 * @param path 文件路径
 */
void Chart4Anything::processDataFlow(QString path) {
  this->originalPipline->processOriginalDataWithUri(path);
}

/**
 * @brief Chart4Anything::getCurrentOriginalFlow 获得当前原始数据流
 * @return QVector&lt;DataEntity*&gt;\&
 */
QVector<DataEntity*>& Chart4Anything::getOriginalFlow() const {
  return *this->originalPipline->getCurrDataFlow();
}

/**
 * @brief Chart4Anything::getDifferentialFlow 获得微分数据流
 * @return QVector&lt;DataEntity*&gt;\&
 */
QVector<DataEntity*>& Chart4Anything::getDifferentialFlow() const {
  return *this->differentialPipline->getCurrDataFlow();
}

/**
 * @brief Chart4Anything::getIntegralFlow 获得积分数据流
 * @return QVector&lt;DataEntity*&gt;\&
 */
QVector<DataEntity*>& Chart4Anything::getIntegralFlow() const {
  return *this->integralPipline->getCurrDataFlow();
}

/**
 * @brief drawOriginalDataFlow 绘制原始通道波形
 */
void Chart4Anything::drawOriginalDataFlow() {
  this->viewCenter->drawDataFlow(&this->getOriginalFlow());
}

/**
 * @brief drawDifferentialDataFlow 绘制微分通道波形
 */
void Chart4Anything::drawDifferentialDataFlow() {
  this->viewCenter->drawDataFlow(&this->getDifferentialFlow());
}

/**
 * @brief drawIntegralDataFlow 绘制积分通道波形
 */
void Chart4Anything::drawIntegralDataFlow() {
  this->viewCenter->drawDataFlow(&this->getIntegralFlow());
}

/**
 * @brief Chart4Anything::getCurrentChartRef 获得内部QChart引用
 * @return
 */
QChart* Chart4Anything::getCurrentChartRef() const {
  return this->viewCenter->getChartRef();
}

/**
 * @brief dealReadDataDone 数据读入完成回调
 * @param fileName 文件名
 * @param fileLength 文件长度 (bytes-number)
 * @param fileContent (bytes-flow)
 */
void Chart4Anything::dealReadDataDone(const QString fileName,
                                      const qint32 fileLength,
                                      QByteArray& fileContent) {
  qDebug() << "we read file " << fileName << " with " << fileLength
           << " bytes.";
}

/**
 * @brief dealOriginalProcessDataDone 原始数据处理完成回调
 * @param fileName 文件名
 * @param dataEntityNumber  数据点个数
 * @param dataUnitList processed-data-flows
 */
void Chart4Anything::dealOriginalProcessDataDone(
    const QString fileName,
    const qint32 dataEntityNumber,
    QVector<DataEntity*>& dataUnitList) {
  qDebug() << "Original process done with file: " << fileName << " . Generate "
           << dataEntityNumber << " DataEntity.";

  // 立即传递给 其他通道处理
  this->differentialPipline->processOriginalData(dataUnitList);
  this->integralPipline->processOriginalData(dataUnitList);
}

/**
 * @brief Chart4Anything::dealExtraProcessDataDone
 * 处理其他通道解析完毕（after-original）
 * @param moduleName 模块名
 * @param dataFlow 数据流引用
 */
void Chart4Anything::dealExtraProcessDataDone(QString moduleName,
                                              QVector<DataEntity*>& dataFlow) {
  qDebug() << "Module:" << moduleName << " process completed!";

  QList<BasePipline*> piplineList;
  piplineList.append(this->originalPipline);
  piplineList.append(this->differentialPipline);
  piplineList.append(this->integralPipline);

  // 全部通道数据整理完毕
  emit allDataFlowReady(piplineList);
}

void Chart4Anything::dealCatchError(ChartException& exception) {
  qDebug() << "!!!Module:" << exception.getModuleName()
           << " get exception:" << exception.getErrorMsg() << "!!!";
}
