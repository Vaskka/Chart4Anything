#include "util.h"

Util::Util()
{

}

/**
 * @brief Util::fromPathGetFileName 使用路径名得到文件名
 * @param path 文件路径
 * @return 文件名
 */
QString Util::fromPathGetFileName(QString path)
{
    if (path.contains('\\')) {
        QString* s = new QString;
        for (int i = path.length() - 1; i >= 0; i--) {
          QChar curr = path.at(i);
          if (curr == '\\') {
            break;
          }

          s->insert(0, path.at(i));
        }
        return *s;

      } else {
        QFileInfo info(path);

        return info.fileName();
      }
}
