# Install script for directory: /home/sel4-training/sel4-tutorials-manifest/projects/seL4_libs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/staging")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4allocman/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4vka/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4utils/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4vspace/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4platsupport/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4serialserver/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4simple/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4simple-default/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4debug/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4test/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4sync/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4muslcsys/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4bench/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/seL4_libs/libsel4vmm/cmake_install.cmake")

endif()

