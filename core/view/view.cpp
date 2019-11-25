#include "view.h"

View::View(QQmlEngine &engine, QObject *parent) : ChartObject("View", parent)
{
    this->engineRef = &engine;
}

void View::draw(QLinkedList<DataEntity *> &list)
{

}
