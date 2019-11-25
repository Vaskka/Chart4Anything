#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QLinkedList>
#include <QQmlEngine>

#include <core/chart_object.h>
#include <entity/dataentity.h>
#include <exception/chart_exception.h>
#include <utils/util.h>

class View : ChartObject
{
private:
    QQmlEngine* engineRef;

signals:
    void drawGraphDone(QString fileName, quint64 dealWithByes);

public:
    View(QQmlEngine& engine, QObject* parent);

    void draw(QLinkedList<DataEntity*>& list);

};

#endif // VIEW_H
