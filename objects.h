#ifndef OBJECTS_H
#define OBJECTS_H
#include <QPainter>
#include <memory>
#include <string>
using namespace std;

// Base class for all vector graphics shapes.
class GraphicsObject {
 public:
  // Dimensions for the object's bounding box.
  double bounding_width;
  double bounding_height;

  // Styling attributes for stroke, and interior color.
  string stroke_color;
  string interior_color;
  double stroke_width;

  GraphicsObject() {}
  virtual ~GraphicsObject() {}

  // Virtual function to convert an object to an SVG string.
  virtual string toSVG() const = 0;

  // Virtual function to render the object using Qt.
  virtual void draw(QPainter& p) const = 0;
  // Virtual function to check if a point is within the boundary.
  virtual bool contains(double x_pressed, double y_pressed) = 0;
  // Virtual function to return a copy of the object.
  virtual std::shared_ptr<GraphicsObject> clone() const = 0;
};

#endif  // OBJECTS_H
