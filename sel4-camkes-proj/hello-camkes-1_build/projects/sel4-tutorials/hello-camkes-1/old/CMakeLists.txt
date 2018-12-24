# @TAG(DATA61_BSD)
cmake_minimum_required(VERSION 3.7.2)

project(hello-camkes-0 C)

ImportCamkes()

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Echo SOURCES components/Echo/src/echo.c)

DeclareCAmkESComponent(EmptyComponent)

DeclareCAmkESRootserver(hello-1.camkes)

GenerateCAmkESRootserver()

# utility CMake functions for the tutorials (not required in normal, non-tutorial applications)
set(FINISH_COMPLETION_TEXT "Component echo saying: hello world")
set(START_COMPLETION_TEXT "Booting all finished, dropped to user space")
configure_file(${CMAKE_SOURCE_DIR}/projects/sel4-tutorials/tools/expect.py ${CMAKE_BINARY_DIR}/check @ONLY)
