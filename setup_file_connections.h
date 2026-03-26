#ifndef SETUP_FILE_CONNECTIONS_H
#define SETUP_FILE_CONNECTIONS_H

#include <QAction>

class MainWindow;

// Links file menu actions to their respective operations.
void setupFileActions(MainWindow* w, QAction* newA, QAction* openA,
                      QAction* saveA, QAction* saveAsA, QAction* closeA);

#endif
