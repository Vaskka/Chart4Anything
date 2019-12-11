#include "global_setting.h"

// single mode
GlobalSetting* GlobalSetting::instance = nullptr;

GlobalSetting::GlobalSetting() : ChartObject("GlobalSetting", nullptr) {}

/**
 * @brief fromQVariantListToQColor 多类型数组转QColor
 * @param list QVariantList
 * @return QColor
 */
QColor GlobalSetting::fromQVariantListToQColor(QList<QVariant> list) {
  QVector<qint32> vector;

  for (QVariant item : list) {
    qint32 value = item.toInt();

    // 处理超过rgb范围
    if (value < 0) {
      value = 0;
    } else if (value > 255) {
      value = 255;
    }

    // 暂存
    vector.push_back(value);
  }

  // 处理颜色不足三维的情况，补足0
  if (vector.length() < 3) {
    for (qint32 i = vector.length(); i < 3; i++) {
      vector.push_back(0);
    }
  }

  QColor color;
  color.setAlphaF(1);
  color.setRed(vector.at(0));
  color.setGreen(vector.at(1));
  color.setBlue(vector.at(2));

  return color;
}

GlobalSetting* GlobalSetting::getInstance() {
  if (instance == nullptr) {
    instance = new GlobalSetting();
  }

  return instance;
}

/**
 * @brief initSetting 初始化全局配置
 * @param settingPath 配置文件路径
 */
void GlobalSetting::initSetting(QString settingPath) {
  // 未读取过配置文件重新读取
  if (!this->ready) {
    QFile file(settingPath);
    QByteArray content;

    if (!file.open(QFile::ReadOnly)) {
      // 文件打不开生成一个默认的配置文件
      QString errorMsg = "无法打开配置文件，已读取默认配置";
      ChartException* exception =
          new ChartException(this->getModuleName(), errorMsg);

      emit parseError(exception);

      file.close();

      file.open(QFile::WriteOnly);
      QByteArray defaultSettingFileContent =
          Util::getExampleSettingFileContent();
      file.write(defaultSettingFileContent);
      file.close();

      content = defaultSettingFileContent;
    } else {
      // 文件成功打开读文件内容
      content = file.readAll();
      file.close();
    }

    QJsonDocument document = QJsonDocument::fromJson(content);
    QJsonObject root = document.object();

    // 一次渲染多少个点
    qint32 eachNodes = root["each_number"].toInt();

    // 原始通道颜色
    QJsonObject color = root["color"].toObject();

    QVariantList originalColor = color["original"].toArray().toVariantList();
    QVariantList differentialColor =
        color["differential"].toArray().toVariantList();
    QVariantList integralColor = color["integral"].toArray().toVariantList();

    // 暂存在map中
    innerSettingMap.insert("each_number", QVariant(eachNodes));
    innerSettingMap.insert("original", QVariant(originalColor));
    innerSettingMap.insert("differential", QVariant(differentialColor));
    innerSettingMap.insert("integral", QVariant(integralColor));

    // 标记初始化已完成
    this->ready = true;
  }
}

/**
 * @brief GlobalSetting::getChannelColor
 * @param channelName
 * @return
 */
QColor GlobalSetting::getChannelColor(QString channelName) {
  QString lower = channelName.toLower();
  if (lower.contains("original")) {
    return fromQVariantListToQColor(innerSettingMap["original"].toList());
  }

  if (lower.contains("differential")) {
    return fromQVariantListToQColor(innerSettingMap["differential"].toList());
  }

  if (lower.contains("integral")) {
    return fromQVariantListToQColor(innerSettingMap["integral"].toList());
  }

  // default color
  return QColor(0, 0, 0);
}

/**
 * @brief getPointNumberEach 获得一次绘制的点的个数
 * @return qint32
 */
qint32 GlobalSetting::getPointNumberEach() {
  return innerSettingMap["each_number"].toInt();
}
