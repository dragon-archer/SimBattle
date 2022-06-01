cmake_minimum_required(VERSION 3.16) # For `target_precompile_headers`

project(SimBattle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILE	localisation/SimBattle_zh_CN.ts
			localisation/qtbase_zh_CN.ts)

set(PROJECT_SOURCES
		main.cpp
		mainwindow.cpp
		mainwindow.h
		pch.cpp
		pch.h
		unit.cpp
		unit.h
		utility.cpp
		utility.h
		${TS_FILE}
)

qt_add_executable(${PROJECT_NAME}
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)

qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILE}
					RESOURCE_PREFIX "/localisation")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_precompile_headers(SimBattle PRIVATE pch.h)
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")

qt_finalize_executable(${PROJECT_NAME})
