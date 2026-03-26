#include "setup_edit_connections.h"
#include <QDebug>
#include "circle.h"
#include "freehand.h"
#include "hexagon.h"
#include "line.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "roundedrectangle.h"
#include "text.h"

// Connects undo, redo, cut, copy, and paste actions to the main window logic.
void setupEditActions(MainWindow* w, QAction* undoAction, QAction* redoAction,
                      QAction* cutAction, QAction* copyAction,
                      QAction* pasteAction) {
  // Manages the undo operation by swapping state with the redo stack.
  QObject::connect(undoAction, &QAction::triggered, w, [w]() {
    if (w->undoStack.empty()) return;
    std::vector<std::shared_ptr<GraphicsObject>> currentSnapshot;
    int n = w->objects.size();
    for (int i = 0; i < n; i++) {
      currentSnapshot.push_back((w->objects)[i]->clone());
    }
    w->redoStack.push(currentSnapshot);
    w->objects = w->undoStack.top();
    w->undoStack.pop(); w->update();
  });
  // Manages the redo operation by restoration from the redo stack.
  QObject::connect(redoAction, &QAction::triggered, w, [w]() {
    if (w->redoStack.empty()) return;
    std::vector<std::shared_ptr<GraphicsObject>> currentSnapshot;
    int n = w->objects.size();
    for (int i = 0; i < n; i++) {
      currentSnapshot.push_back((w->objects)[i]->clone());
    }
    w->undoStack.push(currentSnapshot);
    w->objects = w->redoStack.top();
    w->redoStack.pop();
    w->update();
  });
  // Clones the selected object into the clipboard buffer.
  QObject::connect(copyAction, &QAction::triggered, w, [w]() {
    if (w->selectedObject) {
      w->copiedObject = w->selectedObject->clone();
    }
  });
  // Removes the selected object and saves it to the clipboard.
  QObject::connect(cutAction, &QAction::triggered, w, [w]() {
    if (w->selectedObject) {
      w->saveState();
      w->copiedObject = w->selectedObject->clone();
      int n = w->objects.size();
      for (int i = 0; i < n; ++i) {
        if (w->objects[i] == w->selectedObject) {
          w->objects.erase(w->objects.begin() + i);
          break;
        }
      }
      w->selectedObject = nullptr; w->update();
    }
  });
  // Pastes the clipboard object at the last recorded mouse position.
  QObject::connect(pasteAction, &QAction::triggered, w, [w]() {
    if (w->copiedObject) {
      w->saveState();
      auto newObj = w->copiedObject->clone();
      double targetX = w->previousMouseX;
      double targetY = w->previousMouseY;

      // Moves the pasted object based on its specific shape type.
      if (auto r = std::dynamic_pointer_cast<Rectangle>(newObj)) {
        r->x = targetX; r->y = targetY;
      } else if (auto rr =
                     std::dynamic_pointer_cast<RoundedRectangle>(newObj)) {
        rr->x = targetX; rr->y = targetY;
      } else if (auto c = std::dynamic_pointer_cast<Circle>(newObj)) {
        c->x = targetX; c->y = targetY;
      } else if (auto h = std::dynamic_pointer_cast<Hexagon>(newObj)) {
        h->cx = targetX; h->cy = targetY;
      } else if (auto t = std::dynamic_pointer_cast<Text>(newObj)) {
        t->x = targetX; t->y = targetY;
      } else if (auto l = std::dynamic_pointer_cast<Line>(newObj)) {
        double dx = targetX - l->x1;
        double dy = targetY - l->y1;
        l->x1 += dx; l->y1 += dy;
        l->x2 += dx; l->y2 += dy;
      } else if (auto f = std::dynamic_pointer_cast<Freehand>(newObj)) {
        if (!f->points.empty()) {
          double dx = targetX - f->points[0];
          double dy = targetY - f->points[1];
          for (size_t i = 0; i < f->points.size() - 1; i += 2) {
            f->points[i] += dx; f->points[i + 1] += dy;
          }
        }
      }
      w->objects.push_back(newObj); w->update();
    }
  });
}
