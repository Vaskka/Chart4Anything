#include "data_manager.h"

QMap<QString, QLineSeries*> DataManager::getData2View() const {
  return data2View;
}

DataManager::DataManager(QObject* parent) : QObject(parent) {}

/**
 * @brief insertMap map data into viewable
 * @param moduleName pipline-name
 * @param dataEntityVector dataList
 */
void DataManager::insertMap(QString moduleName,
                            QVector<DataEntity*>& dataEntityVector) {
  QLineSeries* series = new QLineSeries;

  // construct new series
  for (DataEntity* entity : dataEntityVector) {
    series->append(entity->getNo(), entity->getValue());
  }

  if (this->data2View.contains(moduleName)) {
    // free if origin exist
    QLineSeries* currSeries = this->data2View[moduleName];

    delete currSeries;
    currSeries = nullptr;
  }

  // set name
  series->setName(moduleName);

  // from name set color
  if (moduleName.toLower().contains(ORIGINAL_NAME)) {
    series->setColor(
        GlobalSetting::getInstance()->getChannelColor(ORIGINAL_NAME));
  } else if (moduleName.toLower().contains(DIFFERENTIAL_NAME)) {
    series->setColor(
        GlobalSetting::getInstance()->getChannelColor(DIFFERENTIAL_NAME));
  } else if (moduleName.toLower().contains(INTEGRAL_NAME)) {
    series->setColor(
        GlobalSetting::getInstance()->getChannelColor(INTEGRAL_NAME));
  }

  // do mapping
  this->data2View.insert(moduleName, series);

  emit this->mappingDone(moduleName, this->data2View);
}

/**
 * @brief fromChannelGetLineSeries
 * @param channelName channelName
 * @return
 */
QLineSeries* DataManager::fromChannelGetLineSeries(QString channelName) {
  return this->data2View[channelName];
}
