# @TAG(DATA61_BSD)
cmake_minimum_required(VERSION 3.7.2)
#include (../projects/sel4-tutorials/cmake/helpers.cmake)

project(signing_device C)

ImportCamkes()

DeclareCAmkESComponent(Crypto SOURCES components/Crypto/src/crypto.c)
DeclareCAmkESComponent(Modtx  SOURCES components/Modtx/src/modtx.c)
DeclareCAmkESComponent(Modchk SOURCES components/Modchk/src/modchk.c)
DeclareCAmkESComponent(Signtx SOURCES components/Signtx/src/signtx.c)


DeclareCAmkESRootserver(signing_device.camkes)

GenerateCAmkESRootserver()

# utility CMake functions for the tutorials (not required in normal, non-tutorial applications)
#set(FINISH_COMPLETION_TEXT "FAULT HANDLER: data fault from client.control")
#set(START_COMPLETION_TEXT "client: the next instruction will cause a vm fault due to permissions")
#configure_file(${CMAKE_SOURCE_DIR}/projects/sel4-tutorials/tools/expect.py ${CMAKE_BINARY_DIR}/check @ONLY)
