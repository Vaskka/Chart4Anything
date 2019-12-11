#ifndef PIPLINE_H
#define PIPLINE_H

#include <core/chart_object.h>
#include <core/pipline/base_pipline.h>
#include <entity/dataentity.h>
#include <exception/chart_exception.h>
#include <utils/util.h>

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QVector>

class OriginalPipline : public BasePipline {
  Q_OBJECT
 private:
  const qint32 readBytesEach = 256;

 signals:
  void readDataDone(const QString fileName,
                    const qint32 fileLength,
                    QByteArray& fileContent,
                    qint64 offset);

  void processDataDone(const QString fileName,
                       const qint32 dataEntityNumber,
                       QVector<DataEntity*>& dataUnitList);

  void catchError(ChartException& exception);

 public:
  OriginalPipline(QString moduleName, QObject* parent = nullptr);

  void processOriginalDataWithUri(QString path,
                                  qint64 offset = 0,
                                  qint64 length = 50);

 private:
  void readDataFromUri(QString path, qint64 offset, qint64 length);

 private slots:
  void processData(const QString fileName,
                   const qint32 numberOfBytes,
                   QByteArray& data,
                   qint64 offset);
};

#endif  // PIPLINE_H
