#ifndef EXTRACHARTVIEW_H
#define EXTRACHARTVIEW_H

#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

class ExtraChartView : public QChartView {
  Q_OBJECT

 public:
  explicit ExtraChartView(QWidget* parent = nullptr);
  explicit ExtraChartView(QChart* chart, QWidget* parent = nullptr);
 signals:
  /**
   * @brief scroll 平移回调
   * @param dx
   * @param dy
   */
  void ready2Scroll(qint32 dx, qint32 dy);

 private:
  bool mousePressed = false;

  qint32 pressedX;
  qint32 pressedY;

  qint32 releaseX;
  qint32 releaseY;

  /**
   * @brief init 初始化配置
   */
  void init();

  /**
   * @brief mousePressEvent 鼠标按压事件
   * @param event
   */
  void mousePressEvent(QMouseEvent* event) override;

  /**
   * @brief mouseMoveEvent 鼠标移动事件
   * @param event
   */
  void mouseMoveEvent(QMouseEvent* event) override;

  /**
   * @brief mouseReleaseEvent 鼠标释放事件
   * @param event
   */
  void mouseReleaseEvent(QMouseEvent* event) override;

  /**
   * @brief mouseDoubleClickEvent 双击放大
   * @param event
   */
  void mouseDoubleClickEvent(QMouseEvent* event) override;

  /**
   * @brief wheelEvent 滚轮放大
   * @param event
   */
  void wheelEvent(QWheelEvent* event) override;
};

#endif  // EXTRACHARTVIEW_H
