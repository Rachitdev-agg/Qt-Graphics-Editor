#ifndef LINE_H
#define LINE_H

#include "objects.h"

// Class to handle line shapes.
class Line : public GraphicsObject {
 public:
  // Start and end coordinates for the line.
  double x1, y1, x2, y2;

  // Converts the line into a line tag for SVG.
  std::string toSVG() const override;
  // Renders the line using Qt's painter.
  void draw(QPainter& p) const override;
  // Checks if a point is within the line's bounding box.
  bool contains(double x_pressed, double y_pressed) override;
  // Returns a copy of the line object.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif
