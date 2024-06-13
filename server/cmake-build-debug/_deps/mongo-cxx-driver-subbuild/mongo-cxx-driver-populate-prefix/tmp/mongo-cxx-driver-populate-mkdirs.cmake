# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/tmp"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/src/mongo-cxx-driver-populate-stamp"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/src"
  "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/src/mongo-cxx-driver-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/src/mongo-cxx-driver-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-subbuild/mongo-cxx-driver-populate-prefix/src/mongo-cxx-driver-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
