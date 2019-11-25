#include "chart4anything.h"



Chart4Anything::Chart4Anything(QQmlEngine &engine) : ChartObject("Chart4Anything", nullptr)
{
    this->pipline = new Pipline(this);
    this->view = new View(engine, this);
}
