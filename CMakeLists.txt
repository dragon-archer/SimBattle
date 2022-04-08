cmake_minimum_required(VERSION 3.5)

project(SimBattle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES SimBattle_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        pch.h
        pch.cpp
        utility.h
        utility.cpp
        ${TS_FILES}
)

qt_add_executable(SimBattle
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
target_precompile_headers(SimBattle PRIVATE pch.h)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(SimBattle PRIVATE Qt6::Widgets)

qt_finalize_executable(SimBattle)
