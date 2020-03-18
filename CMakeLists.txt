cmake_minimum_required(VERSION 3.5)

project(on-canvas-text-tool LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

pkg_check_modules(RAQM REQUIRED IMPORTED_TARGET raqm)
pkg_check_modules(FC REQUIRED IMPORTED_TARGET fontconfig)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RAQM_INCLUDE_DIRS})

add_executable(
    on-canvas-text-tool
    main.cpp
    mainwindow.cc
    mainwindow.ui
    paintwidget.cc
    layoutengine.cc
    layout.cc
    betterfontcb.cc
)

target_link_libraries(on-canvas-text-tool PRIVATE Qt5::Widgets ${RAQM_LIBRARIES} ${FC_LIBRARIES})
