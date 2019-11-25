#ifndef CHART_4_ANYTHING_H
#define CHART_4_ANYTHING_H

#include <QObject>
#include <core/chart_object.h>
#include <core/pipline/pipline.h>
#include <core/view/view.h>

class Chart4Anything : ChartObject
{
Q_OBJECT
private:
    Pipline* pipline;
    View* view;

public:
    explicit Chart4Anything(QQmlEngine& engine);

};

#endif // CHART4ANYTHING_H
