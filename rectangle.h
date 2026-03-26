#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "objects.h"

// Class to handle rectangle shapes.
class Rectangle : public GraphicsObject {
 public:
  // Top-left coordinates and dimensions.
  double x, y;
  double width, height;

  // Converts the rectangle into a rect tag for SVG.
  std::string toSVG() const override;
  // Renders the rectangle using Qt's painter.
  void draw(QPainter& p) const override;
  // Checks if a point is within the rectangle's boundary.
  bool contains(double x_pressed, double y_pressed) override;
  // Returns a copy of the rectangle object.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif
