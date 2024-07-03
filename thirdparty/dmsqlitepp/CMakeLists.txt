cmake_minimum_required(VERSION 3.21)

PROJECT(dmsqlitepp)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

LibImport("dmsqlitepp" "src/dmsqlitepp")

if (PROJECT_IS_TOP_LEVEL)
	ExeImport("test" "dmsqlitepp")
endif(PROJECT_IS_TOP_LEVEL)