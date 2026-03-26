#include "text.h"

// Write the text tag for the SVG file.
std::string Text::toSVG() const {
  std::string svg = "<text x=\"" + std::to_string(x) + "\" y=\"" +
                    std::to_string(y) + "\" fill=\"" + interior_color +
                    "\" font-size=\"" + std::to_string(fontSize) + "\">" +
                    content + "</text>";

  return svg;
}

// Uses Qt to draw the text on the canvas.
void Text::draw(QPainter& p) const {
  QColor color_text(QString::fromStdString(interior_color));
  p.setPen(color_text);

  QFont font;
  font.setPointSize(fontSize);
  p.setFont(font);

  p.drawText(x, y, QString::fromStdString(content));
}

// Rectangular bounding box check for hit testing.
bool Text::contains(double x_pressed, double y_pressed) {
  // Estimate width based on font size and character count.
  double width = content.length() * fontSize * 0.6;
  double height = fontSize;

  // Boundary check considering text draws from the baseline.
  return x_pressed >= x && x_pressed <= x + width && y_pressed >= y - height &&
         y_pressed <= y;
}

// Clone the current text using smart pointers.
std::shared_ptr<GraphicsObject> Text::clone() const {
  auto t = std::make_shared<Text>();
  *t = *this;
  return t;
}
