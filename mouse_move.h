#ifndef MOUSE_MOVE_H
#define MOUSE_MOVE_H

#include <QMouseEvent>
class MainWindow;

// Updates the canvas state as the mouse moves.
void handleMouseMove(MainWindow* w, QMouseEvent* event);

#endif
