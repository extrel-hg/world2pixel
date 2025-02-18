cmake_minimum_required(VERSION 3.28)

project(world2pixel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(${PROJECT_NAME}
    source/main.cpp
)

#  GEODESK

include(FetchContent)
FetchContent_Declare(geodesk GIT_REPOSITORY https://github.com/clarisma/libgeodesk.git GIT_TAG "origin/main")
FetchContent_MakeAvailable(geodesk)

set(BUILD_SHARED_LIBS OFF)  # Link statically
target_link_libraries(${PROJECT_NAME} geodesk)

# INSTALLATION

set(CMAKE_INSTALL_PREFIX .)
set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION finishedworld2pixel)