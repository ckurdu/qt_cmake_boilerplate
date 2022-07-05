cmake_minimum_required(VERSION 3.15)
include(ptc-standard)

SUBDIRLIST(listlibs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${listlibs})
    message("Test Directory" ${subdir})
    add_subdirectory(${subdir})
endforeach()


