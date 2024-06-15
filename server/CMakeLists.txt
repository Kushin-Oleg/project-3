#установка версий, языка и названия
cmake_minimum_required(VERSION 3.28)
project(server)
set(CMAKE_CXX_STANDARD 20)
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
#библиотека для json
include_directories(include/json/include)
#подключение mongodb
set(ENV{PKG_CONFIG_PATH} /usr/lib/pkgconfig)
find_package(PkgConfig)
pkg_search_module(BSON REQUIRED libbsoncxx)
pkg_search_module(MONGO REQUIRED libmongocxx)

include_directories(server
        ${BSON_INCLUDE_DIRS}
        ${MONGO_INCLUDE_DIRS})
#подключил библиотеку для парсинга таблиц эксель
find_package(Xlnt CONFIG REQUIRED)
#подключил библиотеку для авторизации
set(Poco_DIR "/usr/local/lib/cmake/Poco")
find_package(Poco REQUIRED COMPONENTS Net Foundation)
find_package(Poco REQUIRED COMPONENTS NetSSL)
#добавил мультипарсер для нестандартного файла MIME
include_directories(include/multipart-parser)
#создание исполниельного файла
add_executable(server main.cpp)
target_link_libraries(server PRIVATE jwt-cpp)
target_link_libraries(server PRIVATE OpenSSL::Crypto OpenSSL::SSL)

target_link_libraries(server PRIVATE
        ${BSON_LIBRARIES}
        ${MONGO_LIBRARIES}
)

target_link_libraries(server PRIVATE ${Poco_LIBRARIES})
target_link_libraries(server PRIVATE Poco::NetSSL)

target_link_libraries(server PRIVATE xlnt::xlnt)