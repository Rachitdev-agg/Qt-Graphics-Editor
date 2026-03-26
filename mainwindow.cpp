#include "mainwindow.h"

#include <QPainter>

#include "mouse_move.h"
#include "mouse_press.h"
#include "mouse_release.h"
#include "paint_and_keyboard.h"
#include "setup_edit_connections.h"
#include "setup_file_connections.h"
#include "setup_tool_connections.h"
#include "setup_toolbar.h"

// Main Module to handle all logic flow and event routing
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  initializeMainWindow(this);
}

MainWindow::~MainWindow() {}

// Routes Qt mouse press events to the modular logic handler.
void MainWindow::mousePressEvent(QMouseEvent* event) {
  handleMousePress(this, event);
}

// Routes Qt mouse movement events to the modular logic handler.
void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  handleMouseMove(this, event);
}

// Routes Qt mouse release events to the modular logic handler.
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
  handleMouseRelease(this, event);
}

// Routes Qt paint events to the modular logic handler.
void MainWindow::paintEvent(QPaintEvent*) { handlePaint(this); }

// Routes Qt keyboard events to the text and shortcut handler.
void MainWindow::keyPressEvent(QKeyEvent* event) {
  handleKeyPress(this, event);
}

// Deep-clones the current object list to the undo stack and clears redo
// history.
void MainWindow::saveState() {
  std::vector<std::shared_ptr<GraphicsObject>> snapshot;
  int n = objects.size();
  for (int i = 0; i < n; i++) {
    snapshot.push_back(objects[i]->clone());
  }
  undoStack.push(snapshot);
  // Clear the redo stack when a new action is performed.
  while (!redoStack.empty()) {
    redoStack.pop();
  }
}
