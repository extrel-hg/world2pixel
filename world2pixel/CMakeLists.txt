cmake_minimum_required(VERSION 3.28)

project(world2pixel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB sourcefiles
     "source/*.h"
     "source/*.cpp"
)

add_executable(${PROJECT_NAME}
    ${sourcefiles}
)

#  GEODESK and GEOS

set(GEODESK_WITH_GEOS ON)
set(GEOS_INCLUDE_PATHS "${geos_SOURCE_DIR}/include" "${geos_BINARY_DIR}/capi")

include(FetchContent)
FetchContent_Declare(geodesk GIT_REPOSITORY https://github.com/clarisma/libgeodesk.git GIT_TAG "origin/main")
FetchContent_MakeAvailable(geodesk)

FetchContent_Declare(geos GIT_REPOSITORY https://github.com/libgeos/geos.git GIT_TAG "origin/main")
FetchContent_MakeAvailable(geos)

set(BUILD_SHARED_LIBS OFF)  # Link statically

target_link_libraries(${PROJECT_NAME} geodesk)
target_link_libraries(${PROJECT_NAME} geos_c geos)

# INSTALLATION
set(CMAKE_INSTALL_PREFIX .)
set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION finishedworld2pixel)