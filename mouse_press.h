#ifndef MOUSE_PRESS_H
#define MOUSE_PRESS_H

#include <QMouseEvent>

class MainWindow;

// Logic for initial mouse clicks on the canvas.
void handleMousePress(MainWindow* w, QMouseEvent* event);

#endif
