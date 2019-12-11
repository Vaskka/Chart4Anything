#ifndef UTIL_H
#define UTIL_H

#include <QFileInfo>
#include <QObject>

class Util {
 public:
  Util();

  /**
   * @brief Util::fromPathGetFileName 使用路径名得到文件名
   * @param path 文件路径
   * @return 文件名
   */
  static QString fromPathGetFileName(QString path);

  /**
   * @brief getExampleSettingFileContent 获得示例配置文件bytes
   * @return QString
   */
  static QByteArray getExampleSettingFileContent();
};

#endif  // UTIL_H
