# Install script for directory: /home/kukushka/Рабочий стол/project-3/server/include/mongo-cxx-driver-r3.10.1

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/src/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/cmake/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/data/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/docs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/etc/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mongo-cxx-driver" TYPE FILE FILES
    "/home/kukushka/Рабочий стол/project-3/server/include/mongo-cxx-driver-r3.10.1/LICENSE"
    "/home/kukushka/Рабочий стол/project-3/server/include/mongo-cxx-driver-r3.10.1/README.md"
    "/home/kukushka/Рабочий стол/project-3/server/include/mongo-cxx-driver-r3.10.1/THIRD-PARTY-NOTICES"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/include/mongo-cxx-driver-r3.10.1/generate_uninstall/cmake_install.cmake")
endif()

