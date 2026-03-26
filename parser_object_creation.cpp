#include "parser_object_creation.h"
#include "circle.h"
#include "freehand.h"
#include "hexagon.h"
#include "line.h"
#include "parser_helper.h"
#include "rectangle.h"
#include "roundedrectangle.h"
#include "text.h"

// Extracts common stroke and fill attributes for a graphics object.
void getStyle(std::shared_ptr<GraphicsObject> obj, std::string tag) {
  obj->stroke_color = getAttr(tag, "stroke");
  obj->interior_color = getAttr(tag, "fill");
  obj->stroke_width = getNum(tag, "stroke-width");
}

// Function to create specific shape objects from SVG tags.
std::shared_ptr<GraphicsObject> createGraphicsObject(std::string tag) {
  // Check for circle tag and set attributes.
  if (tag.find("<circle") == 0) {
    auto c = std::make_shared<Circle>();
    c->x = getNum(tag, "cx");
    c->y = getNum(tag, "cy");
    c->radius = getNum(tag, "r");
    getStyle(c, tag);
    return c;
  }

  // Check for rect tag; determines if it is a rounded rectangle.
  if (tag.find("<rect") == 0) {
    if (tag.find("rx=") != std::string::npos) {
      auto rr = std::make_shared<RoundedRectangle>();
      rr->x = getNum(tag, "x");
      rr->y = getNum(tag, "y");
      rr->width = getNum(tag, "width");
      rr->height = getNum(tag, "height");
      rr->rx = getNum(tag, "rx");
      rr->ry = getNum(tag, "ry");
      getStyle(rr, tag);
      return rr;
    }

    auto r = std::make_shared<Rectangle>();
    r->x = getNum(tag, "x");
    r->y = getNum(tag, "y");
    r->width = getNum(tag, "width");
    r->height = getNum(tag, "height");
    getStyle(r, tag);
    return r;
  }

  // Check for line tag and set start/end points.
  if (tag.find("<line") == 0) {
    auto l = std::make_shared<Line>();
    l->x1 = getNum(tag, "x1");
    l->y1 = getNum(tag, "y1");
    l->x2 = getNum(tag, "x2");
    l->y2 = getNum(tag, "y2");
    l->stroke_color = getAttr(tag, "stroke");
    l->stroke_width = getNum(tag, "stroke-width");
    return l;
  }

  // Check for polygon tag used for hexagon implementation.
  if (tag.find("<polygon") != std::string::npos) {
    auto h = std::make_shared<Hexagon>();
    h->cx = getNum(tag, "cx");
    h->cy = getNum(tag, "cy");
    h->radius = getNum(tag, "r");
    std::string a = getAttr(tag, "startAngle");
    h->startAngle = a.empty() ? 0 : std::stod(a);
    getStyle(h, tag);
    return h;
  }

  // Check for text tag and extract inner content.
  if (tag.find("<text") == 0) {
    auto t = std::make_shared<Text>();
    t->x = getNum(tag, "x");
    t->y = getNum(tag, "y");
    t->interior_color = getAttr(tag, "fill");
    t->fontSize = getNum(tag, "font-size");
    if (t->fontSize == 0) t->fontSize = 12;  // Default size if missing.
    t->content = extractContent(tag);
    return t;
  }

  // Check for polyline tag used for freehand sketching.
  if (tag.find("<polyline") != std::string::npos) {
    auto f = std::make_shared<Freehand>();
    f->points = parsePoints(getAttr(tag, "points"));
    f->stroke_color = getAttr(tag, "stroke");
    f->stroke_width = getNum(tag, "stroke-width");
    return f;
  }

  return nullptr;
}
