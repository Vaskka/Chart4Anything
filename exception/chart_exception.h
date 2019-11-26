#ifndef CHARTEXCEPTION_H
#define CHARTEXCEPTION_H


#include <QObject>

class ChartException : QObject
{
private:
    QString moduleName;

    QString errorMsg;

public:
    ChartException(void);

    ChartException(QString moduleName);

    ChartException(QString moduleName, QString msg);


    QString toString();

    /* === getter === */

    QString getErrorMsg() const;

    QString getModuleName() const;

};

#endif // CHARTEXCEPTION_H
