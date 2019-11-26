#include "base_pipline.h"

BasePipline::BasePipline(QString piplineName, QObject* parent)
    : ChartObject(piplineName + "Pipline", parent) {}

/**
 * @brief deleteAndFreeDataEntities 删除容器和释放内部元素内存引用
 * @param vector QVector&lt;DataEntity\*&gt;\*
 */
void BasePipline::deleteAndFreeDataFlow() {
  // 新数据到达释放原数据空间
  if (this->currDataFlow != nullptr) {
    // 释放内部节点的内存
    qDeleteAll(this->currDataFlow->begin(), this->currDataFlow->end());
    this->currDataFlow->clear();

    // 释放容器内存
    delete this->currDataFlow;
    this->currDataFlow = nullptr;
  }
}

/**
 * @brief BasePipline::getCurrDataFlow 取得当前数据流的引用
 * @return QVector&lt;DataEntity\*&gt;\*
 */
QVector<DataEntity*>* BasePipline::getCurrDataFlow() const {
  return this->currDataFlow;
}
