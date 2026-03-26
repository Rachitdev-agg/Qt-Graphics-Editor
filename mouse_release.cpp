#include "mouse_release.h"

#include <algorithm>
#include <cmath>
#include <memory>

#include "circle.h"
#include "freehand.h"
#include "hexagon.h"
#include "line.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "roundedrectangle.h"

// Finalizes drawing, moving, or resizing operations upon mouse button release.
void handleMouseRelease(MainWindow* w, QMouseEvent* event) {
  w->previousMouseX = event->position().x();
  w->previousMouseY = event->position().y();
  w->moving = false;
  w->resizing = false;

  // Prevents creation of zero-size objects if the mouse did not move.
  if (!w->mouseMoved) {
    w->drawing = false;
    return;
  }

  if (w->drawing) {
    // Saves the current canvas state to the undo stack.
    w->saveState();

    // Creates objects based on the active tool.
    if (w->currentTool == "line") {
      auto l = std::make_shared<Line>();
      l->x1 = w->x_start;
      l->y1 = w->y_start;
      l->x2 = w->previousMouseX;
      l->y2 = w->previousMouseY;
      l->stroke_color = w->currentStrokeColor.toStdString();
      l->stroke_width = 2;
      l->interior_color = w->currentFillColor.toStdString();
      w->objects.push_back(l);

    } else if (w->currentTool == "rectangle") {
      auto r = std::make_shared<Rectangle>();
      r->x = std::min(w->x_start, w->previousMouseX);
      r->y = std::min(w->y_start, w->previousMouseY);
      r->width = std::abs(w->previousMouseX - w->x_start);
      r->height = std::abs(w->previousMouseY - w->y_start);
      r->stroke_color = w->currentStrokeColor.toStdString();
      r->interior_color = w->currentFillColor.toStdString();
      r->stroke_width = 2;
      w->objects.push_back(r);

    } else if (w->currentTool == "hexagon") {
      auto h = std::make_shared<Hexagon>();
      h->cx = w->x_start;
      h->cy = w->y_start;
      double dx = w->previousMouseX - w->x_start;
      double dy = w->previousMouseY - w->y_start;
      h->radius = std::sqrt(dx * dx + dy * dy);
      h->startAngle = std::atan2(dy, dx);
      h->stroke_color = w->currentStrokeColor.toStdString();
      h->interior_color = w->currentFillColor.toStdString();
      h->stroke_width = 2;
      w->objects.push_back(h);

    } else if (w->currentTool == "circle") {
      auto c = std::make_shared<Circle>();
      c->x = w->x_start;
      c->y = w->y_start;
      c->radius = std::sqrt(std::pow(w->previousMouseX - w->x_start, 2) +
                            std::pow(w->previousMouseY - w->y_start, 2));
      c->stroke_color = w->currentStrokeColor.toStdString();
      c->interior_color = w->currentFillColor.toStdString();
      c->stroke_width = 2;
      w->objects.push_back(c);

    } else if (w->currentTool == "freehand") {
      auto f = std::make_shared<Freehand>();
      f->points = w->freehandPoints;
      f->stroke_color = w->currentStrokeColor.toStdString();
      f->interior_color = w->currentFillColor.toStdString();
      f->stroke_width = 2;
      w->objects.push_back(f);
      w->freehandPoints.clear();

    } else if (w->currentTool == "roundedrectangle") {
      auto rr = std::make_shared<RoundedRectangle>();
      rr->x = std::min(w->x_start, w->previousMouseX);
      rr->y = std::min(w->y_start, w->previousMouseY);
      rr->width = std::abs(w->previousMouseX - w->x_start);
      rr->height = std::abs(w->previousMouseY - w->y_start);
      rr->rx = 15;
      rr->ry = 15;
      rr->stroke_color = w->currentStrokeColor.toStdString();
      rr->interior_color = w->currentFillColor.toStdString();
      rr->stroke_width = 2;
      w->objects.push_back(rr);
    }
    w->drawing = false;
    w->update();
  }

  // Cleanup temporary state variables after the operation completes.
  w->resizeStartDistance = 0;
  w->originalFreehandPoints.clear();
  w->rectStartX = w->rectStartY = 0;
  w->rrStartX = w->rrStartY = 0;
}
