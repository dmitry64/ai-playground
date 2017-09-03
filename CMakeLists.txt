cmake_minimum_required(VERSION 3.1)

project(ai-playground)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(glm REQUIRED)

include_directories(ui ai)

set(SOURCES
            #ROOT CXX
            main.cxx
            #UI CXX
            ui/mainwindow.cxx
            ui/playgroundwidget.cxx
            ui/fieldwidget.cxx
            #AI CXX
            ai/playground.cxx
            ai/field.cxx
            ai/creature.cxx
)

set(HEADERS
            #UI HPP
            ui/mainwindow.hpp
            ui/playgroundwidget.hpp
            ui/fieldwidget.hpp
            #AI HPP
            ai/simpleneuralnet.hpp
            ai/playground.hpp
            ai/field.hpp
            ai/creature.hpp
)

set(UIFILES
            #UI
            ui/mainwindow.ui
            ui/playgroundwidget.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIFILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets pthread)
