#установка версий, языка и названия
cmake_minimum_required(VERSION 3.28)
project(server)
set(CMAKE_CXX_STANDARD 26)
 #добавил библиотеку http
include_directories(include/cpp-httplib-master)
#добавил библиотеку-сноску где у меня будет реализован функционал приложения
add_library(toolbox STATIC toolbox.h)
set_target_properties(toolbox PROPERTIES LINKER_LANGUAGE CXX)
#добавил библиотеку для jwt токена
#openssl
find_package(OpenSSL REQUIRED)
#jwt
add_subdirectory(include/jwt-cpp)
#json
include_directories(include/json/include/nlohmann)
#создание исполниельного файла
add_executable(server main.cpp)
target_link_libraries(server PRIVATE jwt-cpp)
target_link_libraries(server PRIVATE OpenSSL::Crypto OpenSSL::SSL)
