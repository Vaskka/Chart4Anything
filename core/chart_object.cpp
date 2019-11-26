#include "chart_object.h"


ChartObject::ChartObject(QString moduleName, QObject *parent) : QObject(parent)
{
    this->moduleName = moduleName;
}

QString ChartObject::getModuleName() const
{
    return moduleName;
}
