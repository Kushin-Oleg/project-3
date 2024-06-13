# Install script for directory: /home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmongocxx.so.3.10.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmongocxx.so._noabi"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/libmongocxx.so.3.10.1"
    "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/libmongocxx.so._noabi"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmongocxx.so.3.10.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmongocxx.so._noabi"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/bsoncxx:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/libmongocxx.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1/mongocxx_targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1/mongocxx_targets.cmake"
         "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/CMakeFiles/Export/6d42b658c6c9292e8bf3ee99be0b2687/mongocxx_targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1/mongocxx_targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1/mongocxx_targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1" TYPE FILE FILES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/CMakeFiles/Export/6d42b658c6c9292e8bf3ee99be0b2687/mongocxx_targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1" TYPE FILE FILES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/CMakeFiles/Export/6d42b658c6c9292e8bf3ee99be0b2687/mongocxx_targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mongocxx-3.10.1" TYPE FILE FILES
    "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/mongocxx-config-version.cmake"
    "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/mongocxx-config.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE RENAME "libmongocxx.pc" FILES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/cmake/libmongocxx.pc")
endif()

