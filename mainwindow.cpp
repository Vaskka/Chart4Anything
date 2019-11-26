#include "mainwindow.h"

#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QChart* chart = new QChart();
  this->core = new Chart4Anything(chart, this);

  QChartView* chartView =
      centralWidget()->findChild<QChartView*>("innerwidget");

  chartView->setChart(chart);
}

MainWindow::~MainWindow() {
  delete ui;
}

/**
 * @brief MainWindow::on_selectfile_clicked 选择文件点击回调
 */
void MainWindow::on_selectfile_clicked() {
  QString selectedFilePath =
      QFileDialog::getOpenFileName(this, tr(""), "", tr(""));
  this->core->processDataFlow(selectedFilePath);
  this->core->drawOriginalDataFlow();
}

/**
 * @brief MainWindow::on_show_origin_pipline_triggered 显示原始通道回调
 */
void MainWindow::on_show_origin_pipline_triggered() {
  this->core->drawOriginalDataFlow();
}

/**
 * @brief MainWindow::on_show_differential_pipline_triggered 显示微分通道回调
 */
void MainWindow::on_show_differential_pipline_triggered() {
  this->core->drawDifferentialDataFlow();
}

/**
 * @brief MainWindow::on_show_integral_pipline_triggered 显示积分通道回调
 */
void MainWindow::on_show_integral_pipline_triggered() {
  this->core->drawIntegralDataFlow();
}
