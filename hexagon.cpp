#include "hexagon.h"

#include <cmath>

// Calculate vertices and write the polygon tag.
std::string Hexagon::toSVG() const {
  // Calculating the points.
  std::string points_str = "";
  for (int i = 0; i < 6; i++) {
    double angle = startAngle + i * M_PI / 3.0;
    double x = cx + radius * cos(angle);
    double y = cy + radius * sin(angle);
    points_str += std::to_string(x) + "," + std::to_string(y) + " ";
  }

  // Write the standard 'points' attribute and custom attributes.
  std::string svg = "<polygon points=\"" + points_str + "\" cx=\"" +
                    std::to_string(cx) + "\" cy=\"" + std::to_string(cy) +
                    "\" r=\"" + std::to_string(radius) + "\" startAngle=\"" +
                    std::to_string(startAngle) + "\" stroke=\"" + stroke_color +
                    "\" fill=\"" + interior_color + "\" stroke-width=\"" +
                    std::to_string(stroke_width) + "\" />";

  return svg;
}

// Uses Qt to draw the hexagon based on its six calculated points.
void Hexagon::draw(QPainter& p) const {
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  QColor color_brush(QString::fromStdString(interior_color));
  QBrush brush(color_brush);
  p.setBrush(brush);

  QPolygonF poly;
  for (int i = 0; i < 6; i++) {
    double angle = startAngle + i * M_PI / 3.0;
    double x = cx + radius * cos(angle);
    double y = cy + radius * sin(angle);
    poly << QPointF(x, y);
  }

  p.drawPolygon(poly);
}

// Circular bounding box check for hit testing.
bool Hexagon::contains(double x_pressed, double y_pressed) {
  double x_rel = x_pressed - cx;
  double y_rel = y_pressed - cy;
  return (x_rel * x_rel + y_rel * y_rel) <= radius * radius;
}

// Clone the current hexagon using smart pointers.
std::shared_ptr<GraphicsObject> Hexagon::clone() const {
  auto h = std::make_shared<Hexagon>();
  *h = *this;
  return h;
}
