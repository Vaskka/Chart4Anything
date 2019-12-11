#ifndef DIFFERENTIALVIEW_H
#define DIFFERENTIALVIEW_H

#include <core/view/view_center.h>

class DifferentialView : public ViewCenter {
 public:
  DifferentialView(QChart* chartRef, QObject* parent);
};

#endif  // DIFFERENTIALVIEW_H
