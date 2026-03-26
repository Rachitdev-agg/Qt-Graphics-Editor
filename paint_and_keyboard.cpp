#include "paint_and_keyboard.h"

#include <QDebug>
#include <QFileDialog>
#include <QPainter>

#include "mainwindow.h"
#include "svg_writer.h"

// Renders the static graphics objects and drawing window.
void handlePaint(MainWindow* w) {
  QPainter painter(w);

  // Draw all objects from the main object list.
  for (auto& o : w->objects) {
    o->draw(painter);
  }

  // Renders a dashed line to show the intended shape dimensions.
  if (w->drawing &&
      (w->currentTool == "line" || w->currentTool == "rectangle" ||
       w->currentTool == "circle" || w->currentTool == "hexagon" ||
       w->currentTool == "roundedrectangle")) {
    QPen previewPen(Qt::gray, 2.5, Qt::DashLine);
    painter.setPen(previewPen);
    painter.drawLine(w->x_start, w->y_start, w->x_current, w->y_current);
  }

  // Renders a continuous path for active freehand sketching.
  if (w->drawing && w->currentTool == "freehand" &&
      w->freehandPoints.size() >= 4) {
    painter.setPen(QPen(QColor(w->currentStrokeColor), 2));
    for (int i = 0; i + 3 < w->freehandPoints.size(); i += 2) {
      painter.drawLine(w->freehandPoints[i], w->freehandPoints[i + 1],
                       w->freehandPoints[i + 2], w->freehandPoints[i + 3]);
    }
  }
}

// Processes character input for text objects and manages tool hotkeys.
void handleKeyPress(MainWindow* w, QKeyEvent* event) {

  // Appends or removes characters from the selected text object.
  if (w->editingText && w->editingTextObject) {
    if (event->key() == Qt::Key_Backspace) {
      if (!w->editingTextObject->content.empty())
        w->editingTextObject->content.pop_back();
    } else {
      w->editingTextObject->content += event->text().toStdString();
    }
    w->update();
    return;
  }

  // Global keyboard shortcut for saving the current canvas state.
  if (event->key() == Qt::Key_S) {
    if (w->currentFilePath.isEmpty()) {
      w->currentFilePath = QFileDialog::getSaveFileName(w, "Save", "", "*.svg");
    }
    if (!w->currentFilePath.isEmpty()) {
      SVGwritter writer;
      writer.writeToFile(w->objects, w->currentFilePath.toStdString());
    }
  }

  // Direct tool selection shortcuts for faster workflow.
  if (event->key() == Qt::Key_L) w->currentTool = "line";
  if (event->key() == Qt::Key_R) w->currentTool = "rectangle";
  if (event->key() == Qt::Key_H) w->currentTool = "hexagon";
  if (event->key() == Qt::Key_C) w->currentTool = "circle";
  if (event->key() == Qt::Key_F) w->currentTool = "freehand";
  if (event->key() == Qt::Key_T) w->currentTool = "text";
  if (event->key() == Qt::Key_G) w->currentTool = "roundedrectangle";
}
