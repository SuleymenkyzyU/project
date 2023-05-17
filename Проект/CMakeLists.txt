cmake_minimum_required (VERSION 3.2)
project (TowerBlocks)

# Set OXYGINE_PATH environment variable for using oxygine framework.
set(OXYGINE_PATH $ENV{OXYGINE_PATH})

add_subdirectory(${OXYGINE_PATH} oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_subdirectory(src)
