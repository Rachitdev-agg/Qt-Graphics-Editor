cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0074 NEW)

project(VectorEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt dependencies
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Main UI and application entry sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Core logic, shape classes, and modular event handlers
set(GRAPHICS_SOURCES
    objects.h
    objects.cpp
    circle.h
    circle.cpp
    rectangle.h
    rectangle.cpp
    roundedrectangle.h
    roundedrectangle.cpp
    line.h
    line.cpp
    hexagon.h
    hexagon.cpp
    freehand.h
    freehand.cpp
    text.h
    text.cpp
)

# Parser and File IO modules
set(IO_SOURCES
    parser.h
    parser.cpp
    parser_helper.h
    parser_helper.cpp
    parser_object_creation.h
    parser_object_creation.cpp
    svg_writer.h
    svg_writer.cpp
)

# Event handling and UI setup modules
set(HANDLER_SOURCES
    paint_and_keyboard.h
    paint_and_keyboard.cpp
    mouse_press.h
    mouse_press.cpp
    mouse_move.h
    mouse_move.cpp
    mouse_release.h
    mouse_release.cpp
    setup_toolbar.h
    setup_toolbar.cpp
    setup_file_connections.h
    setup_file_connections.cpp
    setup_edit_connections.h
    setup_edit_connections.cpp
    setup_tool_connections.h
    setup_tool_connections.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VectorEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${GRAPHICS_SOURCES}
        ${IO_SOURCES}
        ${HANDLER_SOURCES}
    )
else()
    add_executable(VectorEditor
        ${PROJECT_SOURCES}
        ${GRAPHICS_SOURCES}
        ${IO_SOURCES}
        ${HANDLER_SOURCES}
    )
endif()

target_link_libraries(VectorEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set bundle properties for cross-platform compatibility
set_target_properties(VectorEditor PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VectorEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VectorEditor)
endif()
