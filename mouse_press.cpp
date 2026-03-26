#include "mouse_press.h"

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
#include "text.h"

// Handles the logic when the mouse button is first pressed.
void handleMousePress(MainWindow* w, QMouseEvent* event) {
  w->moving = false; w->resizing = false;
  w->previousMouseX = event->position().x();
  w->previousMouseY = event->position().y();
  bool foundObject = false;

  // Checks if a point is within the boundary of any existing object.
  int n = static_cast<int>(w->objects.size());
  for (int i = n - 1; i >= 0; --i) {
    if (w->objects[i]->contains(w->previousMouseX, w->previousMouseY)) {
      w->selectedObject = w->objects[i];
      foundObject = true;
      // Calculates distance from the object anchor for move operation.
      if (w->currentTool == "move") {
        w->saveState(); w->moving = true;
        double mx = event->position().x(), my = event->position().y();
        if (auto r = std::dynamic_pointer_cast<Rectangle>(w->selectedObject)) {
          w->moveOffsetX = mx - r->x; w->moveOffsetY = my - r->y;
        } else if (auto rr = std::dynamic_pointer_cast<RoundedRectangle>(
                       w->selectedObject)) {
          w->moveOffsetX = mx - rr->x; w->moveOffsetY = my - rr->y;
        } else if (auto c =
                       std::dynamic_pointer_cast<Circle>(w->selectedObject)) {
          w->moveOffsetX = mx - c->x; w->moveOffsetY = my - c->y;
        } else if (auto h =
                       std::dynamic_pointer_cast<Hexagon>(w->selectedObject)) {
          w->moveOffsetX = mx - h->cx; w->moveOffsetY = my - h->cy;
        } else if (auto t =
                       std::dynamic_pointer_cast<Text>(w->selectedObject)) {
          w->moveOffsetX = mx - t->x; w->moveOffsetY = my - t->y;
        } else if (auto l =
                       std::dynamic_pointer_cast<Line>(w->selectedObject)) {
          w->moveOffsetX = mx - l->x1; w->moveOffsetY = my - l->y1;
        } else if (auto f =
                       std::dynamic_pointer_cast<Freehand>(w->selectedObject)) {
          w->moveOffsetX = mx - f->points[0]; w->moveOffsetY = my - f->points[1];
          w->originalFreehandPoints = f->points;
        }
      }

      // Stores initial geometry parameters for resizing.
      if (w->currentTool == "resize") {
          w->saveState(); w->resizing = true; w->drawing = false;
        if (auto r = std::dynamic_pointer_cast<Rectangle>(w->selectedObject)) {
          w->rectStartX = r->x; w->rectStartY = r->y;
        } else if (auto rr = std::dynamic_pointer_cast<RoundedRectangle>(
                       w->selectedObject)) {
          w->rrStartX = rr->x; w->rrStartY = rr->y;
        } else if (auto f =
                       std::dynamic_pointer_cast<Freehand>(w->selectedObject)) {
          w->originalFreehandPoints = f->points;
          double minX = f->points[0], maxX = f->points[0], minY = f->points[1],
                 maxY = f->points[1];
          for (size_t k = 0; k + 1 < f->points.size(); k += 2) {
            minX = std::min(minX, f->points[k]); maxX = std::max(maxX, f->points[k]);
            minY = std::min(minY, f->points[k + 1]); maxY = std::max(maxY, f->points[k + 1]);
          }
          w->freehandCenterX = (minX + maxX) / 2.0;
          w->freehandCenterY = (minY + maxY) / 2.0;
          double dx = event->position().x() - w->freehandCenterX,
                 dy = event->position().y() - w->freehandCenterY;
          w->resizeStartDistance = std::sqrt(dx * dx + dy * dy);
        }
      }

      // Enables text editing mode if a text object is selected.
      w->editingTextObject = std::dynamic_pointer_cast<Text>(w->selectedObject);
      if (w->editingTextObject) {
        w->editingText = true;
      } else {
        w->editingText = false;
      }
      w->update();
      if (w->currentTool == "move" || w->currentTool == "resize") return;
      break;
    }
  }

  // Resets selection states when clicking on empty canvas space.
  if (!foundObject && w->currentTool != "text") {
    w->editingText = false;
    w->editingTextObject = nullptr;
    w->selectedObject = nullptr;
  }
  if (w->currentTool != "move" && w->currentTool != "resize") {
    w->drawing = true;
    w->mouseMoved = false;
  }
  if (w->currentTool == "freehand") {
    w->freehandPoints.clear();
    w->freehandPoints.push_back(w->previousMouseX);
    w->freehandPoints.push_back(w->previousMouseY);
  }

  // Creates a new text object at the clicked position.
  if (w->currentTool == "text" && !foundObject) {
    w->saveState();
    auto t = std::make_shared<Text>();
    t->x = w->previousMouseX;
    t->y = w->previousMouseY;
    t->content = "Sample Content";
    t->fontSize = 16;
    t->interior_color = w->currentFillColor.toStdString();
    w->objects.push_back(t);
    w->selectedObject = t;
    w->editingText = true;
    w->editingTextObject = t;
    w->update();
    return;
  }
  w->x_start = w->previousMouseX; w->y_start = w->previousMouseY;
  w->x_current = w->x_start; w->y_current = w->y_start;
}
