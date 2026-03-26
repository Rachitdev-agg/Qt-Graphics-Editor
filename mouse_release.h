#ifndef MOUSE_RELEASE_H
#define MOUSE_RELEASE_H

#include <QMouseEvent>
class MainWindow;

// Finalizes drawing or transformation operations on the canvas.
void handleMouseRelease(MainWindow* w, QMouseEvent* event);

#endif
