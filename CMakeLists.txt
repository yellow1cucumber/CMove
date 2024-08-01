cmake_minimum_required(VERSION 3.16)
project(CMove LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp

    CMove.ui
    CMove.h
    CMove.cpp

    PathRepository.h
    PathRepository.cpp

    DirData/PathAnalisys.h
    DirData/PathAnalisys.cpp
)

qt_add_executable(CMove ${PROJECT_SOURCES})

set_target_properties(CMove
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(CMove
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
