#include "setup_tool_connections.h"

#include <QAction>
#include <QColorDialog>

#include "mainwindow.h"

// Connects toolbar and menu actions to the main window's tool state.
void setupToolActions(MainWindow* window, QAction* circleAction,
                      QAction* rectangleAction, QAction* hexagonAction,
                      QAction* lineAction, QAction* textAction,
                      QAction* roundedRectAction, QAction* freehandAction,
                      QAction* moveAction, QAction* resizeAction,
                      QAction* strokeColorAction, QAction* fillColorAction) {
  // Shape and interaction tool connections using lambda functions.
  QObject::connect(lineAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "line"; });

  QObject::connect(rectangleAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "rectangle"; });

  QObject::connect(hexagonAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "hexagon"; });

  QObject::connect(circleAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "circle"; });

  QObject::connect(textAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "text"; });

  QObject::connect(roundedRectAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "roundedrectangle"; });

  QObject::connect(freehandAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "freehand"; });

  QObject::connect(moveAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "move"; });

  QObject::connect(resizeAction, &QAction::triggered, window,
                   [window]() { window->currentTool = "resize"; });

  // Color selection connections using Qt color picker dialogs.
  QObject::connect(strokeColorAction, &QAction::triggered, window, [window]() {
    QColor color = QColorDialog::getColor(Qt::black, window);
    if (color.isValid()) {
      window->currentStrokeColor = color.name();
    }
  });

  QObject::connect(fillColorAction, &QAction::triggered, window, [window]() {
    QColor color = QColorDialog::getColor(Qt::white, window);
    if (color.isValid()) {
      window->currentFillColor = color.name();
    }
  });
}
