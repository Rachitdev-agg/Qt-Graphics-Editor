#ifndef SETUP_EDIT_CONNECTIONS_H
#define SETUP_EDIT_CONNECTIONS_H

#include <QAction>

class MainWindow;

// Links edit menu actions to clipboard and state management logic.
void setupEditActions(MainWindow* w, QAction* undoA, QAction* redoA,
                      QAction* cutA, QAction* copyA, QAction* pasteA);

#endif
