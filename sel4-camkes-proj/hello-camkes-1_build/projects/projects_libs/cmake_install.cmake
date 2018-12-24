# Install script for directory: /home/sel4-training/sel4-tutorials-manifest/projects/projects_libs

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
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libjansson/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libmsgpack/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libringbuffer/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libsdhcdrivers/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libusbdrivers/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libnfs/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libvirtqueue/cmake_install.cmake")
  include("/home/sel4-training/sel4-tutorials-manifest/hello-camkes-1_build/projects/projects_libs/libvswitch/cmake_install.cmake")

endif()

