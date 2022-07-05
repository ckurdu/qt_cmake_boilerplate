include(ptc-standard)

SUBDIRLIST(listlibs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${listlibs})
    message("App Project Adding : " ${subdir})
    add_subdirectory(${subdir})
endforeach()

