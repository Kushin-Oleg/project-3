#установка версий, языка и названия
cmake_minimum_required(VERSION 3.28)
project(server)
set(CMAKE_CXX_STANDARD 26)
 #добавил библиотеку http
include_directories(include/cpp-httplib-master)
#добавил библиотеку-сноску где у меня будет реализован функционал приложения
add_library(toolbox STATIC toolbox.h)
set_target_properties(toolbox PROPERTIES LINKER_LANGUAGE CXX)
#создание исполниельного файла
add_executable(server main.cpp)