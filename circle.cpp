#include "circle.h"

// Build the SVG string with all the circle attributes.
string Circle::toSVG() const {
  string svg = "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) +
               "\" r=\"" + to_string(radius) + "\" stroke=\"" + stroke_color +
               "\" fill=\"" + interior_color + "\" stroke-width=\"" +
               to_string(stroke_width) + "\" />";

  return svg;
}

// Set up the pen and brush to draw the circle on the canvas.
void Circle::draw(QPainter& p) const {
  // Define the border color and thickness.
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  // Define the fill color for the interior.
  QColor color_brush(QString::fromStdString(interior_color));
  QBrush brush(color_brush);
  p.setBrush(brush);

  // Actually draw the circle on the UI.
  p.drawEllipse(QPointF(x, y), radius, radius);
}

// Check to see if a point is inside the circle.
bool Circle::contains(double x_pressed, double y_pressed) {
  double x_rel = x_pressed - x;
  double y_rel = y_pressed - y;
  return (x_rel * x_rel + y_rel * y_rel) <= radius * radius;
}

// Clone the current circle using smart pointers.
std::shared_ptr<GraphicsObject> Circle::clone() const {
  auto c = std::make_shared<Circle>();
  *c = *this;
  return c;
}
