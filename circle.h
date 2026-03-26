#ifndef CIRCLE_H
#define CIRCLE_H

#include "objects.h"

// Class for handling circle shapes in the editor.
class Circle : public GraphicsObject {
 public:
  // Center coords and radius for the circle.
  double x;
  double y;
  double radius;
  Circle() {}
  ~Circle() {}

  // Converts the circle data into an SVG tag string.
  string toSVG() const override;

  // Renders the circle using Qt's painter.
  void draw(QPainter& p) const override;

  // Checks if the user clicked inside the circle area.
  bool contains(double x_pressed, double y_pressed) override;

  // Creates a copy for things like copy-paste.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif  // CIRCLE_H
