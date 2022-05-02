cmake_minimum_required(VERSION 3.14)

project(ModelPlugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ModelPlugin
	SHARED

	plugin.h
	mymodel.h

	plugin.cpp
	mymodel.cpp
	)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Qml)

target_link_libraries(
	ModelPlugin
	PRIVATE
	Qt5::Core
	Qt5::Quick
	Qt5::Qml
	)

file(COPY qmldir DESTINATION ${CMAKE_BINARY_DIR})
