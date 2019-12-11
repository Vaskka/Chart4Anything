#include "extra_chart_view.h"

ExtraChartView::ExtraChartView(QWidget* parent) : QChartView(parent) {
  this->init();
}

ExtraChartView::ExtraChartView(QChart* chart, QWidget* parent)
    : QChartView(chart, parent) {
  this->init();
}

/**
 * @brief ExtraChartView::init 初始化配置
 */
void ExtraChartView::init() {
  this->setTransformationAnchor(QChartView::AnchorUnderMouse);
  this->setResizeAnchor(QChartView::AnchorUnderMouse);
}

/**
 * @brief mousePressEvent 鼠标按压事件
 * @param event
 */
void ExtraChartView::mousePressEvent(QMouseEvent* event) {
  this->mousePressed = true;
  this->pressedX = event->pos().x();
  this->pressedY = event->pos().y();

  qDebug() << "Press in x:" << this->pressedX << " y:" << this->pressedY;
}

/**
 * @brief mouseMoveEvent 鼠标移动事件
 * @param event
 */
void ExtraChartView::mouseMoveEvent(QMouseEvent* event) {}

/**
 * @brief mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void ExtraChartView::mouseReleaseEvent(QMouseEvent* event) {
  this->mousePressed = false;
  this->releaseX = event->pos().x();
  this->releaseY = event->pos().y();

  qint32 dx = this->releaseX - this->pressedX;
  qint32 dy = this->releaseY - this->pressedY;

  emit ready2Scroll(-dx, dy);
  this->chart()->scroll(-dx, dy);
}

/**
 * @brief mouseDoubleClickEvent 双击放大
 * @param event
 */
void ExtraChartView::mouseDoubleClickEvent(QMouseEvent* event) {
  this->chart()->scroll(20, 20);
}

/**
 * @brief wheelEvent 滚轮放大
 * @param event
 */
void ExtraChartView::wheelEvent(QWheelEvent* event) {
  this->chart()->scroll(event->delta(), event->delta());
}
