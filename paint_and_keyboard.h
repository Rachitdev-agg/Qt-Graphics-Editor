#ifndef EXTRA_LOGIC_H
#define EXTRA_LOGIC_H

#include <QKeyEvent>
class MainWindow;

// Logic for rendering the canvas and processing keyboard input.
void handlePaint(MainWindow* w);
void handleKeyPress(MainWindow* w, QKeyEvent* event);

#endif
