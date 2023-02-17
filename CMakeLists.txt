cmake_minimum_required (VERSION 3.13.4)
project(nanopb-simple C)

include(InitialiseToolchain)
initialise_toolchain()

set(GENERATED ${CMAKE_CURRENT_BINARY_DIR}/generated)

add_custom_command(
  COMMAND ${NANOPB_PROTOC} -I${CMAKE_CURRENT_SOURCE_DIR}
                           --nanopb_out=${GENERATED}
                           simple.proto
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/simple.proto
  OUTPUT ${GENERATED}/simple.pb.c)

add_executable(simple simple.c ${GENERATED}/simple.pb.c)
target_include_directories(simple PRIVATE ${GENERATED})
target_link_libraries(simple ufw protobuf-nanopb-static)
MakeStrictCompilerC(simple)
set_target_cpu(simple)
