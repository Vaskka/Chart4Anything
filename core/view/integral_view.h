#ifndef INTEGRALVIEW_H
#define INTEGRALVIEW_H

#include <core/view/view_center.h>

class IntegralView : public ViewCenter {
 public:
  IntegralView(QChart* chartRef, QObject* parent);
};

#endif  // INTEGRALVIEW_H
