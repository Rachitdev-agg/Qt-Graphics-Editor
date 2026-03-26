# Vector Graphics Editor - COP 290 Course Project

## 1. Project Overview

This Vector Graphics Editor is a C++ application built using the Qt Framework.

The project emphasizes:

- Clean modular architecture
- Strict separation of concerns
- Smart pointer usage
- Undo/Redo state management
- Custom SVG parsing and serialization
- Google C++ Style Guide compliance

The editor allows users to create, manipulate, and persist vector-based geometric designs using a graphical interface.

---

## 2. Build & Run Instructions

### Requirements

- CMake ≥ 3.16
- Qt 6 (or Qt 5.15+)
- C++17 compatible compiler

---

### Step 1: Create Build Directory

```bash
mkdir build
cd build
```

### Step 2: Configure Project

If Qt is installed system-wide:

```bash
cmake ..
```

If Qt is installed in a custom directory:

```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/qt ..
```

Example (macOS Qt installer):

```bash
cmake -DCMAKE_PREFIX_PATH=/Users/yourname/Qt/6.x.x/macos ..
```

### Step 3: Build

```bash
make
```

### Step 4: Run

On macOS:

```bash
open VectorEditor.app
```

or

```bash
./VectorEditor.app/Contents/MacOS/VectorEditor
```

On Linux:

```bash
./VectorEditor
```

On Windows:

```
VectorEditor.exe
```

---

## 3. Features & How to Use

### A. Drawing Tools

Select a tool from the toolbar or use the shortcut key.

**Line (L)**  
Click and drag to define start and end points.

**Rectangle (R)**  
Click and drag to create a rectangle.

**Circle (C)**  
Click to define center, drag to set radius.

**Hexagon (H)**  
Click to define center, drag to set radius of regular hexagon.

**Rounded Rectangle (G)**  
Works like rectangle but with predefined corner radius.

**Freehand (F)**  
Click and drag to draw a continuous path.

**Text (T)**  
Click on canvas to create text.  
Start typing immediately.  
Click elsewhere or switch tool to exit text editing mode.

---

### B. Selection, Move & Resize

**Smart Selection**

Click on any shape to select it.

Objects are checked from top to bottom so the shape drawn last is selected first when shapes overlap.

**Move Tool**

Select the Move tool.  
Click on a shape.  
Drag to reposition it.

**Resize Tool**

Select the Resize tool.  
Click and drag anywhere on the shape to resize it.

Rectangles: width/height adjust.  
Circle/Hexagon: radius adjusts.  
Freehand: scaled proportionally about center.  
Text: font size adjusts.

---

### C. Edit Menu Features

**Copy**

Select a shape.  
Click Edit → Copy.  
Shape is stored in memory.

**Cut**

Select a shape.  
Click Edit → Cut.  
Shape is copied and removed from canvas.

**Paste**

Click on desired location.  
Click Edit → Paste.  
Copied shape appears at last clicked position.

---

### D. Color Selection

Use the Colors menu:

**Set Stroke Color**

Changes boundary color of selected or newly created shapes.

**Set Fill Color**

Changes interior color of selected or newly created shapes.

Fill Colors are applied to:

- Rectangles
- Circles
- Hexagons
- Rounded Rectangles
- Text (fill color)

---

### E. File Operations

**New**

Clears current canvas.

**Open**

Opens an existing SVG file (restricted subset supported).

**Save**

Saves current diagram to existing file.

**Save As**

Saves to a new SVG file.

**Close**

Closes the application.

---

### F. Undo / Redo

Every drawing, move, resize, cut, or paste action is stored.

Undo reverses the last action.

Redo reapplies the undone action.

---

## 4. Keyboard Shortcuts

| Key | Action                 |
| --- | ---------------------- |
| L   | Line Tool              |
| R   | Rectangle Tool         |
| C   | Circle Tool            |
| H   | Hexagon Tool           |
| G   | Rounded Rectangle Tool |
| F   | Freehand Tool          |
| T   | Text Tool              |
| S   | Save SVG               |

---

## 5. Technical Design

### 100-Line File Constraint

To comply with assignment requirements:

Event logic separated into:

- mouse_press.cpp
- mouse_move.cpp
- mouse_release.cpp
- paint_and_keyboard.cpp

Parser split into:

- Attribute extraction helpers
- Object creation modules
- Control unit

UI signal-slot connections modularized into:

- setup_toolbar.cpp
- setup_file_connections.cpp
- setup_edit_connections.cpp
- setup_tool_connections.cpp

No source file exceeds 100 lines.

---

### Design Patterns Used

**Polymorphism**

All shapes inherit from GraphicsObject  
Common interface: draw(), toSVG(), clone()

**Factory-style Object Creation**

Parser instantiates shape objects based on detected XML tag.

**Memento Pattern**

Undo/Redo implemented via snapshot stacks.

---

## 6. Project Structure

```
VectorEditor/
├── CMakeLists.txt
├── main.cpp
├── mainwindow.h / mainwindow.cpp
├── objects.h / objects.cpp
├── circle.h / circle.cpp
├── rectangle.h / rectangle.cpp
├── roundedrectangle.h / roundedrectangle.cpp
├── line.h / line.cpp
├── hexagon.h / hexagon.cpp
├── freehand.h / freehand.cpp
├── text.h / text.cpp
├── parser.h / parser.cpp
├── svg_writer.h / svg_writer.cpp
└── event handler modules
```
