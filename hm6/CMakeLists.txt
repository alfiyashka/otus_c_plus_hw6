cmake_minimum_required(VERSION 3.28.3)


set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(hw6 VERSION ${PROJECT_VERSION} LANGUAGES C CXX)


configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set ( SRC_HEADER
   src/Matrix.hpp
   src/MatrixValueType.hpp
   src/Point.hpp
)
set ( SRC
   src/Point.cpp
)

add_executable(hw6 ${SRC_HEADER} ${SRC} main.cpp)

set_property(TARGET hw6 PROPERTY CXX_STANDARD 20)


include("functions.cmake")
generate_packages(${PROJECT_NAME})

