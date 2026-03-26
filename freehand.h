#ifndef FREEHAND_H
#define FREEHAND_H
#include "objects.h"

// Handles freehand sketching by storing a series of connected points.
class Freehand : public GraphicsObject {
 public:
  // List of coordinates stored as x1, y1, x2, y2, etc.
  vector<double> points;

  // Generates a polyline tag for the SVG file.
  string toSVG() const override;

  // Renders the sketch by drawing lines between consecutive points.
  void draw(QPainter& p) const override;

  // Checks if a click is within the bounding box of the sketch.
  bool contains(double x_pressed, double y_pressed) override;

  // Creates a copy of the sketch object.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif
