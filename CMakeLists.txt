cmake_minimum_required(VERSION 3.23)
project(learn_pybind)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/pybind11)


pybind11_add_module(mymod src/main.cpp)


add_custom_command(
        TARGET mymod  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_BINARY_DIR}/$<CONFIGURATION> ${CMAKE_CURRENT_LIST_DIR}/python
        )