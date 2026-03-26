#include "roundedrectangle.h"

// Write the rect tag with corner radii for the SVG file.
std::string RoundedRectangle::toSVG() const {
  std::string svg = "<rect x=\"" + std::to_string(x) + "\" y=\"" +
                    std::to_string(y) + "\" width=\"" + std::to_string(width) +
                    "\" height=\"" + std::to_string(height) + "\" rx=\"" +
                    std::to_string(rx) + "\" ry=\"" + std::to_string(ry) +
                    "\" stroke=\"" + stroke_color + "\" fill=\"" +
                    interior_color + "\" stroke-width=\"" +
                    std::to_string(stroke_width) + "\" />";

  return svg;
}

// Uses Qt to draw the rectangle with rounded corners on the canvas.
void RoundedRectangle::draw(QPainter& p) const {
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  QColor color_brush(QString::fromStdString(interior_color));
  QBrush brush(color_brush);
  p.setBrush(brush);

  p.drawRoundedRect(x, y, width, height, rx, ry);
}

// Rectangular bounding box check for hit testing.
bool RoundedRectangle::contains(double x_pressed, double y_pressed) {
  // Simplified check ignoring the rounded corner gaps.
  return x_pressed >= x && x_pressed <= x + width && y_pressed >= y &&
         y_pressed <= y + height;
}

// Clone the current rounded rectangle using smart pointers.
std::shared_ptr<GraphicsObject> RoundedRectangle::clone() const {
  auto rr = std::make_shared<RoundedRectangle>();
  *rr = *this;
  return rr;
}
