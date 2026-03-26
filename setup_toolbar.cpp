#include "setup_toolbar.h"

#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "mainwindow.h"
#include "setup_edit_connections.h"
#include "setup_file_connections.h"
#include "setup_tool_connections.h"

// Sets up the UI components including the menu bar and the vertical shape
// toolbar.
void initializeMainWindow(MainWindow* w) {
  w->menuBar()->setNativeMenuBar(false);
  w->setMinimumSize(800, 600);

  // Initialize the vertical toolbar for quick access to drawing tools.
  QToolBar* shapeToolBar = new QToolBar("Shapes", w);
  w->addToolBar(Qt::LeftToolBarArea, shapeToolBar);
  shapeToolBar->setOrientation(Qt::Vertical);

  // Setup File menu with standard file operations.
  QMenuBar* bar = w->menuBar();
  QMenu* fileMenu = bar->addMenu("File");
  QAction* saveAction = fileMenu->addAction("Save");
  QAction* newAction = fileMenu->addAction("New");
  QAction* openAction = fileMenu->addAction("Open");
  QAction* SaveasAction = fileMenu->addAction("Save as");
  QAction* closeAction = fileMenu->addAction("Close");

  // Setup Edit menu for modifications and clipboard actions.
  QMenu* editMenu = bar->addMenu("Edit");
  QAction* cutAction = editMenu->addAction("Cut");
  QAction* copyAction = editMenu->addAction("Copy");
  QAction* pasteAction = editMenu->addAction("Paste");
  QAction* undoAction = editMenu->addAction("Undo");
  QAction* redoAction = editMenu->addAction("Redo");

  // Define actions for all supported geometric shapes and tools.
  QMenu* toolsMenu = bar->addMenu("Tools");
  QAction* circleAction = new QAction("Circle", w);
  QAction* rectangleAction = new QAction("Rectangle", w);
  QAction* hexagonAction = new QAction("Hexagon", w);
  QAction* lineAction = new QAction("Line", w);
  QAction* textAction = new QAction("Text", w);
  QAction* roundedrectangleAction = new QAction("Rounded Rectangle", w);
  QAction* freehandAction = new QAction("Freehand", w);
  QAction* moveAction = toolsMenu->addAction("Move");
  QAction* resizeAction = toolsMenu->addAction("Resize");

  // Add shape selection actions to the left-side toolbar.
  shapeToolBar->addAction(lineAction);
  shapeToolBar->addAction(rectangleAction);
  shapeToolBar->addAction(circleAction);
  shapeToolBar->addAction(hexagonAction);
  shapeToolBar->addAction(textAction);
  shapeToolBar->addAction(roundedrectangleAction);
  shapeToolBar->addAction(freehandAction);

  // Setup Color menu for stroke and fill adjustments.
  QMenu* colorMenu = bar->addMenu("Colors");
  QAction* strokeColorAction = colorMenu->addAction("Set Stroke Color");
  QAction* fillColorAction = colorMenu->addAction("Set Fill Color");

  // Link UI actions to their respective logic handlers.
  setupFileActions(w, newAction, openAction, saveAction, SaveasAction,
                   closeAction);
  setupEditActions(w, undoAction, redoAction, cutAction, copyAction,
                   pasteAction);
  setupToolActions(w, circleAction, rectangleAction, hexagonAction, lineAction,
                   textAction, roundedrectangleAction, freehandAction,
                   moveAction, resizeAction, strokeColorAction,
                   fillColorAction);
}
