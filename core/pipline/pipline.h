#ifndef PIPLINE_H
#define PIPLINE_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QLinkedList>

#include <core/chart_object.h>
#include <entity/dataentity.h>
#include <exception/chart_exception.h>
#include <utils/util.h>

class Pipline : ChartObject
{
    Q_OBJECT
private:
    const qint32 readBytesEach = 256;

signals:
    void readDataDone(const QString fileName, const quint64 fileLength, QByteArray& fileContent);

    void processDataDone(const QString fileName, const quint64 dataEntityNumber, const QLinkedList<DataEntity*>& dataUnitList);

    void catchError(ChartException& exception);

public:
    Pipline(QObject* parent = nullptr);

    void readDataFromUri(QString path);

    void processData(QString fileName, quint64 numberOfBytes, QByteArray& data);
};

#endif // PIPLINE_H
