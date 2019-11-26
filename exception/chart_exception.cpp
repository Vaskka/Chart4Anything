#include "chart_exception.h"


ChartException::ChartException(void)
{
    this->errorMsg = QString("Unknown message.");
    this->moduleName = QString("Unknow module name.");
}

ChartException::ChartException(QString moduleName)
{
    this->errorMsg = QString("Unknown message.");
    this->moduleName = QString(moduleName);
}

ChartException::ChartException(QString moduleName, QString msg)
{
    this->moduleName = moduleName;
    this->errorMsg = msg;
}

QString ChartException::toString()
{
    QString output;

    // append error infomation
    output.append("Catch exception in module:");
    output.append(this->moduleName);
    output.append(". The error message is:");
    output.append(this->errorMsg);
    output.append('.');

    return output;
}

/* === getter === */


QString ChartException::getModuleName() const
{
    return moduleName;
}


QString ChartException::getErrorMsg() const
{
    return errorMsg;
}
