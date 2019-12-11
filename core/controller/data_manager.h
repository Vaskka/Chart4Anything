#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <core/common.h>
#include <core/global_setting.h>
#include <entity/dataentity.h>

#include <QMap>
#include <QObject>
#include <QVector>
#include <QtCharts>

class DataManager : public QObject {
  Q_OBJECT
 private:
  QMap<QString, QLineSeries*> data2View;

 signals:
  void mappingDone(QString channelName,
                   QMap<QString, QLineSeries*>& currentDataMapping);

 public:
  explicit DataManager(QObject* parent = nullptr);

  /**
   * @brief insertMap map data into viewable
   * @param channelName channelName
   * @param dataEntityVector dataList
   */
  void insertMap(QString channelName, QVector<DataEntity*>& dataEntityVector);

  /**
   * @brief fromChannelGetLineSeries
   * @param channelName channelName
   * @return
   */
  QLineSeries* fromChannelGetLineSeries(QString channelName);

  QMap<QString, QLineSeries*> getData2View() const;

 public slots:
};

#endif  // DATAMANAGER_H
