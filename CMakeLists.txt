# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# project name
project( pid-quantizacao-uniforme )

# flags

# include
include_directories( ./src )

#target
add_executable( quantizacao-uniforme  ./src/main.cpp )

add_executable( DisplayImage ./src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

