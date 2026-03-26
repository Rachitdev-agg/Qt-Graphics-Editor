#include "setup_file_connections.h"

#include <QFileDialog>

#include "mainwindow.h"
#include "parser.h"
#include "svg_writer.h"

// Links file menu actions to file system operations.
void setupFileActions(MainWindow* w, QAction* newAction, QAction* openAction,
                      QAction* saveAction, QAction* saveAsAction,
                      QAction* closeAction) {
  // Resets the workspace for a new file.
  QObject::connect(newAction, &QAction::triggered, w, [w]() {
    w->currentFilePath = "";
    w->objects.clear();
    w->update();
  });

  // Closes the main application window.
  QObject::connect(closeAction, &QAction::triggered, w, [w]() { w->close(); });

  // Saves current objects to an SVG file using existing or new path.
  QObject::connect(saveAction, &QAction::triggered, w, [w]() {
    if (w->currentFilePath.isEmpty()) {
      w->currentFilePath = QFileDialog::getSaveFileName(w, "Save", "", "*.svg");
    }
    if (!w->currentFilePath.isEmpty()) {
      SVGwritter writer;
      writer.writeToFile(w->objects, w->currentFilePath.toStdString());
    }
  });

  // Forces a file dialog to save the current drawing under a new name.
  QObject::connect(saveAsAction, &QAction::triggered, w, [w]() {
    QString fileName = QFileDialog::getSaveFileName(w, "Save As", "", "*.svg");
    if (!fileName.isEmpty()) {
      SVGwritter writer;
      writer.writeToFile(w->objects, fileName.toStdString());
    }
  });

  // Opens an SVG file and setup the window via the parser.
  QObject::connect(openAction, &QAction::triggered, w, [w]() {
    QString fileName = QFileDialog::getOpenFileName(w, "Open", "", "*.svg");
    if (!fileName.isEmpty()) {
      SVGParser parser;
      w->objects = parser.parse(fileName.toStdString());
      w->currentFilePath = fileName;
      w->update();
    }
  });
}
