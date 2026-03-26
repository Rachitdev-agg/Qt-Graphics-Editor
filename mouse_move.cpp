#include "mouse_move.h"

#include <algorithm>
#include <cmath>

#include "circle.h"
#include "freehand.h"
#include "hexagon.h"
#include "line.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "roundedrectangle.h"
#include "text.h"

// Updates object positions or dimensions as the mouse moves across the canvas.
void handleMouseMove(MainWindow* w, QMouseEvent* event) {
  double curr_x = event->position().x();
  double curr_y = event->position().y();

  // Updates preview coordinates or appends points for freehand drawing.
  if (w->drawing) {
    w->mouseMoved = true;
    w->x_current = curr_x;
    w->y_current = curr_y;
    if (w->currentTool == "freehand") {
      w->freehandPoints.push_back(curr_x);
      w->freehandPoints.push_back(curr_y);
    }
    w->update();
  }

  // Translates the selected object by calculating current position minus
  // initial offset.
  if (w->currentTool == "move" && w->moving && w->selectedObject) {
    if (auto r = std::dynamic_pointer_cast<Rectangle>(w->selectedObject)) {
      r->x = curr_x - w->moveOffsetX;
      r->y = curr_y - w->moveOffsetY;

    } else if (auto rr = std::dynamic_pointer_cast<RoundedRectangle>(
                   w->selectedObject)) {
      rr->x = curr_x - w->moveOffsetX;
      rr->y = curr_y - w->moveOffsetY;

    } else if (auto c = std::dynamic_pointer_cast<Circle>(w->selectedObject)) {
      c->x = curr_x - w->moveOffsetX;
      c->y = curr_y - w->moveOffsetY;

    } else if (auto h = std::dynamic_pointer_cast<Hexagon>(w->selectedObject)) {
      h->cx = curr_x - w->moveOffsetX;
      h->cy = curr_y - w->moveOffsetY;

    } else if (auto t = std::dynamic_pointer_cast<Text>(w->selectedObject)) {
      t->x = curr_x - w->moveOffsetX;
      t->y = curr_y - w->moveOffsetY;

    } else if (auto l = std::dynamic_pointer_cast<Line>(w->selectedObject)) {
      double dx = (curr_x - w->moveOffsetX) - l->x1;
      double dy = (curr_y - w->moveOffsetY) - l->y1;
      l->x1 += dx;
      l->y1 += dy;
      l->x2 += dx;
      l->y2 += dy;

    } else if (auto f =
                   std::dynamic_pointer_cast<Freehand>(w->selectedObject)) {
      double dx = (curr_x - w->moveOffsetX) - f->points[0];
      double dy = (curr_y - w->moveOffsetY) - f->points[1];
      for (size_t i = 0; i + 1 < f->points.size(); i += 2) {
        f->points[i] += dx;
        f->points[i + 1] += dy;
      }
    }
    w->update();
    return;
  }

  // Implements resizing based on the distance between current and previous
  // mouse positions.
  if (w->currentTool == "resize" && w->resizing && w->selectedObject) {
    double delta_x = curr_x - w->previousMouseX;
    double delta_y = curr_y - w->previousMouseY;

    if (auto r = std::dynamic_pointer_cast<Rectangle>(w->selectedObject)) {
      r->x = std::min(w->rectStartX, curr_x);
      r->y = std::min(w->rectStartY, curr_y);
      r->width = std::abs(curr_x - w->rectStartX);
      r->height = std::abs(curr_y - w->rectStartY);

    } else if (auto rr = std::dynamic_pointer_cast<RoundedRectangle>(
                   w->selectedObject)) {
      rr->x = std::min(w->rrStartX, curr_x);
      rr->y = std::min(w->rrStartY, curr_y);
      rr->width = std::abs(curr_x - w->rrStartX);
      rr->height = std::abs(curr_y - w->rrStartY);

    } else if (auto c = std::dynamic_pointer_cast<Circle>(w->selectedObject)) {
      c->radius =
          std::sqrt(std::pow(curr_x - c->x, 2) + std::pow(curr_y - c->y, 2));
    } else if (auto h = std::dynamic_pointer_cast<Hexagon>(w->selectedObject)) {
      h->radius =
          std::sqrt(std::pow(curr_x - h->cx, 2) + std::pow(curr_y - h->cy, 2));

    } else if (auto l = std::dynamic_pointer_cast<Line>(w->selectedObject)) {
      l->x2 += delta_x;
      l->y2 += delta_y;
    } else if (auto t = std::dynamic_pointer_cast<Text>(w->selectedObject)) {
      t->fontSize = std::max(5.0, t->fontSize + delta_y);

    } else if (auto f =
                   std::dynamic_pointer_cast<Freehand>(w->selectedObject)) {
      // Scales freehand paths relative to the center of the bounding box.
      double dist = std::sqrt(std::pow(curr_x - w->freehandCenterX, 2) +
                              std::pow(curr_y - w->freehandCenterY, 2));
      if (w->resizeStartDistance != 0) {
        double scale = dist / w->resizeStartDistance;
        for (size_t i = 0; i + 1 < w->originalFreehandPoints.size(); i += 2) {
          f->points[i] =
              w->freehandCenterX +
              (w->originalFreehandPoints[i] - w->freehandCenterX) * scale;
          f->points[i + 1] =
              w->freehandCenterY +
              (w->originalFreehandPoints[i + 1] - w->freehandCenterY) * scale;
        }
      }
    }
    w->previousMouseX = curr_x;
    w->previousMouseY = curr_y;
    w->update();
  }
}
