cmake_minimum_required(VERSION 3.0.0)
project(cppmake VERSION 0.1.0)

include(CTest)
enable_testing()

ADD_LIBRARY(libmodule
    src/sqlite/sqlite3.c 
    src/sqlite/sqlite3.h
    src/sqlite/sqlite3ext.h
)

add_executable(cppmake main.cpp)
target_link_libraries(cppmake libmodule)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
