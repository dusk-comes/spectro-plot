cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME spectroplot)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SRC mainwindow.cpp main.cpp)
set(UI mainwindow.ui)
set(PROJECT_FILES ${SRC} ${UI})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

Include(FetchContent)
FetchContent_Declare(
    sonoplayer
    GIT_REPOSITORY https://github.com/dusk-comes/sonoplayer.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(sonoplayer)

add_subdirectory(QCustomPlot-library)
add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC Qt${QT_VERSION_MAJOR}::Core
        PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport
        PRIVATE qcustomplot
        PRIVATE sonoplayer)

target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)
