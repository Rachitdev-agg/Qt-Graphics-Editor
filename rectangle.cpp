#include "rectangle.h"

#include <algorithm>

// Write the rect tag for the SVG file.
std::string Rectangle::toSVG() const {
  std::string svg = "<rect x=\"" + std::to_string(x) + "\" y=\"" +
                    std::to_string(y) + "\" width=\"" + std::to_string(width) +
                    "\" height=\"" + std::to_string(height) + "\" stroke=\"" +
                    stroke_color + "\" fill=\"" + interior_color +
                    "\" stroke-width=\"" + std::to_string(stroke_width) +
                    "\" />";

  return svg;
}

// Uses Qt to draw the rectangle on the canvas.
void Rectangle::draw(QPainter& p) const {
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  QColor color_brush(QString::fromStdString(interior_color));
  QBrush brush(color_brush);
  p.setBrush(brush);

  p.drawRect(x, y, width, height);
}

// Rectangular bounding box check for hit testing.
bool Rectangle::contains(double x_pressed, double y_pressed) {
  // Determine bounds to handle potential negative width or height.
  double minX = std::min(x, x + width);
  double maxX = std::max(x, x + width);
  double minY = std::min(y, y + height);
  double maxY = std::max(y, y + height);

  return x_pressed >= minX && x_pressed <= maxX && y_pressed >= minY &&
         y_pressed <= maxY;
}

// Clone the current rectangle using smart pointers.
std::shared_ptr<GraphicsObject> Rectangle::clone() const {
  auto r = std::make_shared<Rectangle>();
  *r = *this;
  return r;
}
