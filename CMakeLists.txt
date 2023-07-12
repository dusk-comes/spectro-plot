cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME realtime_plot)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS PrintSupport REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

include_directories(.)
set(SRC mainwindow.cpp qcustomplot.cpp main.cpp)
set(UI mainwindow.ui)
set(PROJECT_FILES ${SRC} ${UI})

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport)
