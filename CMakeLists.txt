cmake_minimum_required(VERSION 2.8)
project(WestonCodingChallenge)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} include/ )

add_executable(AStarSolver src/main.cpp src/Map.cpp)
target_link_libraries(AStarSolver ${OpenCV_LIBS} )