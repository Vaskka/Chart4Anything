#include <QApplication>

#include "mainwindow.h"

#define CHART_DEBUG false

void debug();

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show();
  return a.exec();
}

#include <core/global_setting.h>
void debug() {
  GlobalSetting::getInstance()->initSetting("__setting.json");
  qDebug() << GlobalSetting::getInstance()->getPointNumberEach();
  qDebug() << GlobalSetting::getInstance()->getChannelColor("original");
  qDebug() << GlobalSetting::getInstance()->getChannelColor("differential");
  qDebug() << GlobalSetting::getInstance()->getChannelColor("integral");
}
