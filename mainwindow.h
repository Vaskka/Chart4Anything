#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
   * @brief MainWindow::on_show_origin_pipline_triggered 显示原始通道点击回调
   */
  void on_show_origin_pipline_triggered();

  /**
   * @brief MainWindow::on_show_differential_pipline_triggered 显示微分通道回调
   */
  void on_show_differential_pipline_triggered();

  void on_show_integral_pipline_triggered();

 private:
  Ui::MainWindow* ui;

  Chart4Anything* core;
};
#endif  // MAINWINDOW_H
