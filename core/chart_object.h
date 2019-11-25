#ifndef CHART_OBJECT_H
#define CHART_OBJECT_H

#include <QObject>


class ChartObject : public QObject
{
protected:
    QString moduleName;

public:

    //explicit ChartObject();

    explicit ChartObject(QString moduleName, QObject *parent = nullptr);

    /* === Getter === */

    QString getModuleName() const;
};

#endif // CHARTOBJECT_H
