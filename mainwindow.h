#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <stack>
#include <vector>

#include "objects.h"
#include "text.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Central class managing the application state and event routing.
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  // Coordinate storage for shape transformations and selection.
  double rectStartX, rectStartY;
  double rrStartX, rrStartY;
  std::vector<double> originalFreehandPoints;
  double freehandCenterX, freehandCenterY, resizeStartDistance;
  double moveOffsetX = 0, moveOffsetY = 0;

  // State variables for various interaction modes.
  bool editingText = false;
  bool resizing = false;
  bool moving = false, mouseMoved = false;
  bool drawing = false;

  // Object management using smart pointers and stacks for undo/redo.
  std::shared_ptr<Text> editingTextObject = nullptr;
  std::stack<std::vector<std::shared_ptr<GraphicsObject>>> redoStack;
  std::stack<std::vector<std::shared_ptr<GraphicsObject>>> undoStack;
  std::shared_ptr<GraphicsObject> copiedObject = nullptr;
  std::shared_ptr<GraphicsObject> selectedObject = nullptr;
  std::vector<std::shared_ptr<GraphicsObject>> objects;

  // Current tool settings and file metadata.
  QString currentFilePath;
  QString currentStrokeColor = "black", currentFillColor = "white";
  int currentStrokeWidth = 2;
  std::vector<double> freehandPoints;
  std::string currentTool = "line";
  double x_start, y_start, x_current, y_current;
  double previousMouseX = 0, previousMouseY = 0;

  // Captures a deep copy of the current canvas for state management.
  void saveState();

 protected:
  // Event handlers overridden from QMainWindow to connect to modular helpers.
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private:
  Ui::MainWindow* ui;
};
#endif
