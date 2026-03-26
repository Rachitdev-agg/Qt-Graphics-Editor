#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include "rectangle.h"

// Class to handle rectangles with rounded corners.
class RoundedRectangle : public Rectangle {
 public:
  // Corner radii for the x and y axes.
  double rx, ry;

  // Converts the rounded rectangle into a rect tag with rx and ry for SVG.
  std::string toSVG() const override;
  // Renders the rounded rectangle using Qt's painter.
  void draw(QPainter& p) const override;
  // Checks if a point is within the rectangle's boundary.
  bool contains(double x_pressed, double y_pressed) override;
  // Returns a copy of the rounded rectangle object.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif
