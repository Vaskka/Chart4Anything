#include "chart4anything.h"

Chart4Anything::Chart4Anything(QChart* originalChartRef,
                               QChart* differentialChartRef,
                               QChart* integralChartRef,
                               QObject* parent)
    : ChartObject("Chart4Anything", parent) {
  // 初始化配置
  GlobalSetting::getInstance()->initSetting(SETTING_PATH);

  // model 层
  this->originalPipline = new OriginalPipline("Original", this);
  this->integralPipline = new IntegralPipline("Integer", this);
  this->differentialPipline = new DifferentialPipline("Differential", this);

  // controller 层
  this->controller = new DataManager;

  // view 层
  this->originalView = new OriginalView(originalChartRef, this);
  this->differentialView = new DifferentialView(differentialChartRef, this);
  this->integralView = new IntegralView(integralChartRef, this);

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

  // 连接视图映射完成回调
  connect(this->controller, &DataManager::mappingDone, this,
          &Chart4Anything::dealMappingDone);
}

/**
 * @brief processDataFlow 指定文件路径 并处理成各个通道的结果
 * @param path 文件路径
 */
void Chart4Anything::processDataFlow(QString path,
                                     qint64 offset,
                                     qint64 length) {
  this->currentFilePath = path;
  this->originalPipline->processOriginalDataWithUri(path, offset, length);
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
 * @brief resetOffset
 * 重置信号偏移，当前数据释放，重新从文件的offset读取length个data，并传递给对应通道处理
 * @param offset 偏移量
 * @param length 长度
 */
void Chart4Anything::resetOffset(qint64 offset, qint64 length) {
  if (!this->currentFilePath.isNull()) {
    // 当前文件已经处理过才会执行resetOffset(qint64, qint64);
    this->originalPipline->processOriginalDataWithUri(this->currentFilePath,
                                                      offset, length);
  }
}

/**
 * @brief drawOriginalChannal 绘制原始通道
 */
void Chart4Anything::drawOriginalChannal() {
  this->originalView->drawFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->originalPipline->getModuleName()));
}

/**
 * @brief drawDifferentialChannel 绘制微分通道
 */
void Chart4Anything::drawDifferentialChannel() {
  this->differentialView->drawFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->differentialPipline->getModuleName()));
}

/**
 * @brief drawIntegralChannel 绘制积分通道
 */
void Chart4Anything::drawIntegralChannel() {
  this->integralView->drawFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->integralPipline->getModuleName()));
}

/**
 * @brief removeOriginChannel 移除原始通道图像
 */
void Chart4Anything::removeOriginChannel() {
  this->originalView->removeFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->originalPipline->getModuleName()));
}

/**
 * @brief removeDifferentialChannel 移除微分通道图像
 */
void Chart4Anything::removeDifferentialChannel() {
  this->differentialView->removeFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->differentialPipline->getModuleName()));
}

/**
 * @brief removeIntegralChannel 移除积分通道图像
 */
void Chart4Anything::removeIntegralChannel() {
  this->integralView->removeFlowWithLineSeries(
      this->controller->fromChannelGetLineSeries(
          this->integralPipline->getModuleName()));
}

/**
 * @brief getCurrentOriginalChartRef 当前chart的引用
 * @return
 */
QChart* Chart4Anything::getCurrentOriginalChartRef() const {
  return this->originalView->getChartRef();
}

/**
 * @brief getCurrentDifferentialChartRef 获得微分的chart引用
 * @return
 */
QChart* Chart4Anything::getCurrentDifferentialChartRef() const {
  return this->differentialView->getChartRef();
}

/**
 * @brief getCurrentIntegralChartRef 获得积分的chart引用
 * @return
 */
QChart* Chart4Anything::getCurrentIntegralChartRef() const {
  return this->integralView->getChartRef();
}

/**
 * @brief getDataMapping 获取数据视图mapping
 * @return QMap
 */
QMap<QString, QLineSeries*> Chart4Anything::getDataLineSeriesMapping() const {
  return this->controller->getData2View();
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

  // do original mapping
  this->controller->insertMap(this->originalPipline->getModuleName(),
                              dataUnitList);
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

  // 添加通道和视图映射
  controller->insertMap(moduleName, dataFlow);
}

void Chart4Anything::dealCatchError(ChartException& exception) {
  qDebug() << "!!!Module:" << exception.getModuleName()
           << " get exception:" << exception.getErrorMsg() << "!!!";
}

/**
 * @brief dealMappingDone 处理数据视图映射完成回调
 * @param channelName 通道名称
 * @param currentMapping currentMapping
 */
void Chart4Anything::dealMappingDone(
    QString channelName,
    QMap<QString, QLineSeries*>& currentMapping) {
  // 根据通道名渲染对应的图像
  if (channelName == this->originalPipline->getModuleName()) {
    // 渲染原始图像
    this->originalView->drawFlowWithLineSeries(currentMapping[channelName]);
  } else if (channelName == this->differentialView->getModuleName()) {
    // 渲染微分图像
    this->differentialView->drawFlowWithLineSeries(currentMapping[channelName]);
  } else if (channelName == this->integralView->getModuleName()) {
    // 渲染积分图像
    this->integralView->drawFlowWithLineSeries(currentMapping[channelName]);
  }
}
