# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# project name
project( pid-rgb2gray )

# flags

# include
include_directories( ./src )

#target
add_executable( rgb2gray  ./src/main.cpp )

add_executable( DisplayImage ./src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

