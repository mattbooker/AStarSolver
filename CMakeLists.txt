cmake_minimum_required(VERSION 2.8)
project(WestonCodingChallenge)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} include/ )

# Optimization flags
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")

add_executable(AStarSolver src/main.cpp src/CostMap.cpp src/AStar.cpp)
target_link_libraries(AStarSolver ${OpenCV_LIBS} )