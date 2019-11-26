#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QFileInfo>

class Util
{
public:
    Util();

    /**
     * @brief Util::fromPathGetFileName 使用路径名得到文件名
     * @param path 文件路径
     * @return 文件名
     */
    static QString fromPathGetFileName(QString path);
};

#endif // UTIL_H
