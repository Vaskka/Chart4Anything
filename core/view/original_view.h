#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <core/view/view_center.h>

class OriginalView : public ViewCenter {
 public:
  OriginalView(QChart* chartRef, QObject* parent);
};

#endif  // ORIGINALVIEW_H
