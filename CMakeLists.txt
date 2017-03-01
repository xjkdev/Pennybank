cmake_minimum_required(VERSION 2.8)

project(pennybank)

aux_source_directory(./src SRC_LIST)

SET(CMAKE_C_FLAGS "-O2")

SET(EXECUTABLE_OUTPUT_PATH ./bin)
ADD_EXECUTABLE(main ${SRC_LIST})
