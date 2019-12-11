#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <extra/extra_chart_view.h>

#include <QMainWindow>

#include "chart4anything.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  /**
   * @brief MainWindow::on_selectfile_clicked 选择文件点击回调
   */
  void on_selectfile_clicked();

  /**
   * @brief on_originalChannelShow_triggered 原始通道显示回调
   */
  void on_originalChannelShow_triggered();

  /**
   * @brief on_originalChannelRemove_triggered 原始通道关闭回调
   */
  void on_originalChannelRemove_triggered();

  /**
   * @brief on_differentialChannelShow_triggered 微分通道显示回调
   */
  void on_differentialChannelShow_triggered();

  /**
   * @brief on_differentChannelRemove_triggered 微分通道关闭回调
   */
  void on_differentChannelRemove_triggered();

  /**
   * @brief on_integralChannelShow_triggered 积分通道显示回调
   */
  void on_integralChannelShow_triggered();

  /**
   * @brief on_integralChannelRemove_triggered 积分通道关闭回调
   */
  void on_integralChannelRemove_triggered();

  /**
   * @brief on_reset_clicked 重置按钮点击回调
   */
  void on_reset_clicked();

  /**
   * @brief originalScroll 原始通道平移回调
   * @param dx
   * @param dy
   */
  void dealWithScroll(qint32 dx, qint32 dy);

 private:
  Ui::MainWindow* ui;

  Chart4Anything* core;

  ExtraChartView* original;
  ExtraChartView* different;
  ExtraChartView* integral;

  // file length control
  qint64 offset = 0;
};
#endif  // MAINWINDOW_H
