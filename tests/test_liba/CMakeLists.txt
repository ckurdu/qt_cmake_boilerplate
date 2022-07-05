cmake_minimum_required(VERSION 3.5)

project(testliba LANGUAGES CXX)
include(ptc-standard)

#printTargets()

set(beTestedLib LibA)
set(beTestedLibDir liba)

#[[
if(NOT TARGET ${testLib})
    add_subdirectory("../${testLib} ${testLib}_fortest")
endif()
]]

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testliba tst_liba.cpp testdata.qrc)
add_test(NAME testliba COMMAND testliba)

getLibSourceDir(${beTestedLibDir} libsource)
message("Lib Source Dir ${libsource}")
target_include_directories(testliba PUBLIC ${libsource})

target_link_libraries(testliba PRIVATE Qt${QT_VERSION_MAJOR}::Test ${beTestedLib})


