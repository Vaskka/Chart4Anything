#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QChart* originalChart = new QChart();
  QChart* differentialChart = new QChart();
  QChart* integralChart = new QChart();

  this->core =
      new Chart4Anything(originalChart, differentialChart, integralChart, this);

  ExtraChartView* originalChartView =
      centralWidget()->findChild<ExtraChartView*>("originalChartView");

  ExtraChartView* differentialChartView =
      centralWidget()->findChild<ExtraChartView*>("differentialChartView");

  ExtraChartView* integralChartView =
      centralWidget()->findChild<ExtraChartView*>("integralChartView");

  originalChartView->setChart(originalChart);
  differentialChartView->setChart(differentialChart);
  integralChartView->setChart(integralChart);

  this->original = originalChartView;
  this->different = differentialChartView;
  this->integral = integralChartView;

  connect(this->original, &ExtraChartView::ready2Scroll, this,
          &MainWindow::dealWithScroll);
  connect(this->different, &ExtraChartView::ready2Scroll, this,
          &MainWindow::dealWithScroll);
  connect(this->integral, &ExtraChartView::ready2Scroll, this,
          &MainWindow::dealWithScroll);
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
  this->core->processDataFlow(
      selectedFilePath, 0, GlobalSetting::getInstance()->getPointNumberEach());
}

/**
 * @brief MainWindow::on_originalChannelShow_triggered 原始通道show
 */
void MainWindow::on_originalChannelShow_triggered() {
  this->core->drawOriginalChannal();
}

/**
 * @brief MainWindow::on_originalChannelRemove_triggered 原始通道remove
 */
void MainWindow::on_originalChannelRemove_triggered() {
  this->core->removeOriginChannel();
}

/**
 * @brief MainWindow::on_differentialChannelShow_triggered 微分通道show
 */
void MainWindow::on_differentialChannelShow_triggered() {
  this->core->drawDifferentialChannel();
}

/**
 * @brief MainWindow::on_differentChannelRemove_triggered 微分通道remove
 */
void MainWindow::on_differentChannelRemove_triggered() {
  this->core->removeDifferentialChannel();
}

/**
 * @brief MainWindow::on_integralChannelShow_triggered 积分通道show
 */
void MainWindow::on_integralChannelShow_triggered() {
  this->core->drawIntegralChannel();
}

/**
 * @brief MainWindow::on_integralChannelRemove_triggered 积分通道remove
 */
void MainWindow::on_integralChannelRemove_triggered() {
  this->core->removeIntegralChannel();
}

/**
 * @brief on_reset_clicked 重置按钮点击回调
 */
void MainWindow::on_reset_clicked() {
  this->original->chart()->zoomReset();
  this->different->chart()->zoomReset();
  this->integral->chart()->zoomReset();
}

/**
 * @brief originalScroll 通道平移回调
 * @param dx
 * @param dy
 */
void MainWindow::dealWithScroll(qint32 dx, qint32 dy) {
  this->offset += dx;

  if (offset < 0) {
    offset = 0;
  }
  this->core->resetOffset(this->offset,
                          GlobalSetting::getInstance()->getPointNumberEach());
}
