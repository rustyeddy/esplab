# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

*include($ENV{MDF_PATH}/project.cmake)

set_property(TARGET mqtt_example PROPERTY CXX_STANDARD 11)

project(mqtt_example)
