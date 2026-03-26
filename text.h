#ifndef TEXT_H
#define TEXT_H

#include "objects.h"

// Class to handle text objects.
class Text : public GraphicsObject {
 public:
  // Anchor coordinates and the string to display.
  double x;
  double y;
  string content;

  // Converts the text into a text tag for SVG.
  string toSVG() const override;
  double fontSize = 14;
  // Renders the text using Qt's painter.
  void draw(QPainter& p) const override;
  // Checks if a point is within the text's boundary.
  bool contains(double x_pressed, double y_pressed) override;
  // Returns a copy of the text object.
  std::shared_ptr<GraphicsObject> clone() const override;
};

#endif
