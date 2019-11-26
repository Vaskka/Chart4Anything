#include "original_pipline.h"

QVector<DataEntity*>* OriginalPipline::getCurrDataFlow() const {
  return currDataFlow;
}

OriginalPipline::OriginalPipline(QObject* parent)
    : ChartObject("OriginalPipline", parent) {
  connect(this, &OriginalPipline::readDataDone, this,
          &OriginalPipline::processData);
}

void OriginalPipline::processOriginalDataWithUri(QString path) {
  this->readDataFromUri(path);
}

void OriginalPipline::readDataFromUri(QString path) {
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
  QDataStream in(&file);
  qint32 bytesCount = 0;
  char* rawDataBuffer;

  // init in heap
  QByteArray* content = new QByteArray;

  while (!in.atEnd()) {
    int n = in.readRawData(rawDataBuffer, this->readBytesEach);
    // cal read bytes number
    bytesCount += n;
    // save in QbyteArray
    content->append(rawDataBuffer);
  }

  // notify upper app that read is done
  emit readDataDone(fileName, bytesCount, *content);
}

void OriginalPipline::processData(QString fileName,
                                  qint32 numberOfBytes,
                                  QByteArray& data) {
  // make sure data have even bytes
  // becase of short take 2 bytes

  if (numberOfBytes % 2 != 0) {
    // copy last byte
    data.append(data.at(numberOfBytes - 1));
    numberOfBytes++;
  }

  // all of data entity will init in the heap
  // 新数据到达释放原数据空间
  if (this->currDataFlow != nullptr) {
    delete this->currDataFlow;
    this->currDataFlow = nullptr;
  }

  for (qint32 i = 0; i < numberOfBytes; i += 2) {
    qint32 higherPart = data.at(i);
    qint32 lowerPart = data.at(i + 1);

    // cal value
    qint16 value = 0;
    value += (higherPart << 8);
    value += lowerPart;

    // init data entity
    DataEntity* entity = new DataEntity(i, value);

    this->currDataFlow->append(entity);
  }

  // notify upper app that process is done
  emit processDataDone(fileName, numberOfBytes, *this->currDataFlow);
}
