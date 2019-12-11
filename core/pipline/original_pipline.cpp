#include "original_pipline.h"

#include <core/global_setting.h>

OriginalPipline::OriginalPipline(QString moduleName, QObject* parent)
    : BasePipline(moduleName, parent) {
  connect(this, &OriginalPipline::readDataDone, this,
          &OriginalPipline::processData);
}

void OriginalPipline::processOriginalDataWithUri(QString path,
                                                 qint64 offset,
                                                 qint64 length) {
  this->readDataFromUri(path, offset, length);
}

void OriginalPipline::readDataFromUri(QString path,
                                      qint64 offset,
                                      qint64 length) {
  QFile file(path);
  QString fileName = Util::fromPathGetFileName(path);

  // read file
  if (!file.open(QFile::ReadOnly)) {
    QString errorMsg;
    errorMsg += "file:";
    errorMsg += path;
    errorMsg += " read error. Error msg:";
    errorMsg += file.errorString();

    ChartException exception(this->moduleName, errorMsg);
    emit catchError(exception);
    return;
  }

  // read data
  QFileInfo fileInfo(file);
  QByteArray content;

  if (file.seek(offset)) {
    content += file.read(length);
  }

  file.close();
  // read data length
  qint32 bytesCount = content.length();

  // notify upper app that read is done
  emit readDataDone(fileName, bytesCount, content, offset);
}

void OriginalPipline::processData(QString fileName,
                                  qint32 numberOfBytes,
                                  QByteArray& data,
                                  qint64 offset) {
  // make sure data have even bytes
  // becase of short take 2 bytes
  if (numberOfBytes % 2 != 0) {
    // copy last byte
    data.append(data.at(numberOfBytes - 1));
    numberOfBytes++;
  }

  // 新数据到达释放原数据空间
  this->deleteAndFreeDataFlow();

  this->currDataFlow = new QVector<DataEntity*>;
  for (qint32 i = 0; i < numberOfBytes - 1; i += 2) {
    qint32 higherPart = data.at(i);
    qint32 lowerPart = data.at(i + 1);

    // cal value
    qint16 value = 0;
    value += (higherPart << 8);
    value += lowerPart;

    // init data entity
    DataEntity* entity = new DataEntity(offset + i, value);

    this->currDataFlow->append(entity);
  }

  // notify upper app that process is done
  emit processDataDone(fileName, numberOfBytes, *this->currDataFlow);
}
