cmake_minimum_required(VERSION 3.5)

project(Nexor)

# Укажите, что требуется C++ компилятор g++
set(CMAKE_CXX_COMPILER "g++")

# Укажите путь для сборки проекта в папку "debug"
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# Установите путь для собранных исполняемых файлов в папку "files"
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# Добавьте исходные файлы вашего проекта
add_executable(Nexor main.cpp Interpreter.hpp globals.hpp Interpreter.cpp)
