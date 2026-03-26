#include "line.h"

#include <algorithm>

// Write the line tag for the SVG file.
std::string Line::toSVG() const {
  std::string svg = "<line x1=\"" + std::to_string(x1) + "\" y1=\"" +
                    std::to_string(y1) + "\" x2=\"" + std::to_string(x2) +
                    "\" y2=\"" + std::to_string(y2) + "\" stroke=\"" +
                    stroke_color + "\" stroke-width=\"" +
                    std::to_string(stroke_width) + "\" />";

  return svg;
}

// Uses Qt to draw the line between two points.
void Line::draw(QPainter& p) const {
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  p.drawLine(x1, y1, x2, y2);
}

// Rectangular bounding box check for hit testing.
bool Line::contains(double x_pressed, double y_pressed) {
  // Finding the rectangular bounding box.
  double minX = std::min(x1, x2);
  double maxX = std::max(x1, x2);
  double minY = std::min(y1, y2);
  double maxY = std::max(y1, y2);

  return x_pressed >= minX && x_pressed <= maxX && y_pressed >= minY &&
         y_pressed <= maxY;
}

// Clone the current line using smart pointers.
std::shared_ptr<GraphicsObject> Line::clone() const {
  auto l = std::make_shared<Line>();
  *l = *this;
  return l;
}
