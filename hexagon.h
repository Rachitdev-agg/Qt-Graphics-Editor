#ifndef HEXAGON_H
#define HEXAGON_H

#include "objects.h"

// Class to handle regular hexagon shapes.
class Hexagon : public GraphicsObject {
 public:
  // Center coordinates and the outer radius.
  double cx;
  double cy;
  double radius;

  // Converts the hexagon into a polygon tag for SVG.
  string toSVG() const override;
  // Renders the hexagon by calculating its six vertices.
  void draw(QPainter& p) const override;
  // Checks if a point is within the hexagon's boundary.
  bool contains(double x_pressed, double y_pressed) override;
  // Returns a copy of the hexagon object.
  std::shared_ptr<GraphicsObject> clone() const override;
  // Stores initial angle for a rotated hexagon.
  double startAngle;
};

#endif
