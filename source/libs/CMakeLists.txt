include(ptc-standard)

SUBDIRLIST(listlibs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${listlibs})
    message("Lib Directory" ${subdir})
    add_subdirectory(${subdir})
endforeach()
