#ifndef SETUP_TOOL_CONNECTIONS_H
#define SETUP_TOOL_CONNECTIONS_H

#include <QAction>
class MainWindow;

// Links UI actions to the window's tool selection and color state.
void setupToolActions(MainWindow* w, QAction* circleAction,
                      QAction* rectangleAction, QAction* hexagonAction,
                      QAction* lineAction, QAction* textAction,
                      QAction* roundedRectAction, QAction* freehandAction,
                      QAction* moveAction, QAction* resizeAction,
                      QAction* strokeColorAction, QAction* fillColorAction);

#endif
