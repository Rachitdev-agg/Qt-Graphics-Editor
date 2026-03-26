#include "freehand.h"

#include <QPainter>
#include <QPen>
#include <sstream>
#include <vector>

// Converts the point vector into an SVG polyline string.
std::string Freehand::toSVG() const {
  std::stringstream pointsStream;
  // Format points as "x1,y1 x2,y2 ..." for the SVG standard.
  for (size_t i = 0; i + 1 < points.size(); i += 2) {
    pointsStream << points[i] << "," << points[i + 1] << " ";
  }

  std::string svg = "<polyline points=\"" + pointsStream.str() +
                    "\" stroke=\"" + stroke_color +
                    "\" fill=\"none\" stroke-width=\"" +
                    std::to_string(stroke_width) + "\" />";

  return svg;
}

// Iterates through points to draw segments on the canvas.
void Freehand::draw(QPainter& p) const {
  if (points.size() < 4) return;  // need at least 2 points to draw a line.

  // Setting stroke color and width.
  QColor color_stroke(QString::fromStdString(stroke_color));
  QPen pen(color_stroke);
  pen.setWidth(stroke_width);
  p.setPen(pen);

  // Draw lines between each pair of consecutive points.
  for (int i = 0; i + 3 < points.size(); i += 2) {
    p.drawLine(points[i], points[i + 1], points[i + 2], points[i + 3]);
  }
}

// Bounding box logic to detect if the sketch was clicked.
bool Freehand::contains(double x_pressed, double y_pressed) {
  if (!points.empty()) {
    double minX = points[0], maxX = points[0];
    double minY = points[1], maxY = points[1];

    // Find the outer limits of the sketch.
    for (size_t i = 0; i + 1 < points.size(); i += 2) {
      minX = std::min(minX, points[i]);
      maxX = std::max(maxX, points[i]);
      minY = std::min(minY, points[i + 1]);
      maxY = std::max(maxY, points[i + 1]);
    }

    return x_pressed >= minX && x_pressed <= maxX && y_pressed >= minY &&
           y_pressed <= maxY;
  }

  return false;
}

// Clone for the undo/redo stack.
std::shared_ptr<GraphicsObject> Freehand::clone() const {
  auto f = std::make_shared<Freehand>();
  *f = *this;
  return f;
}
