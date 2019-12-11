#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H

#include <exception/chart_exception.h>
#include <utils/util.h>

#include <QColor>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QVariant>

#include "chart_object.h"

class GlobalSetting : public ChartObject {
  Q_OBJECT

 signals:
  /**
   * @brief parseError 配置文件解析错误
   * @param exception 异常object
   */
  void parseError(ChartException* exception);

 private:
  explicit GlobalSetting();
  GlobalSetting(const GlobalSetting&);
  GlobalSetting& operator=(const GlobalSetting&);

  bool ready = false;

  QMap<QString, QVariant> innerSettingMap;

  static GlobalSetting* instance;

  /**
   * @brief fromQVariantListToQColor 多类型数组转QColor
   * @param list QVariantList
   * @return QColor
   */
  QColor fromQVariantListToQColor(QList<QVariant> list);

 public:
  static GlobalSetting* getInstance();

  /**
   * @brief initSetting 初始化全局配置
   * @param settingPath 配置文件路径
   */
  void initSetting(QString settingPath);

  /**
   * @brief getChannelColor 获得指定通道的颜色
   * @param channelName 通道名
   * @return QColor
   */
  QColor getChannelColor(QString channelName);

  /**
   * @brief getPointNumberEach 获得一次绘制的点的个数
   * @return qint32
   */
  qint32 getPointNumberEach();
};

#endif  // GLOBALSETTING_H
