# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

find_package( OpenCV REQUIRED )

# project name
project( pid-quantizacao-uniforme )

# flags

# include
include_directories( ./src )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${OpenCV_DIRS} )

#target
add_executable( quantizacao-uniforme  ./src/main.cpp ./src/pid_utils.cpp)

add_executable( DisplayImage ./src/DisplayImage.cpp ./src/pid_utils.cpp)
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

add_executable( test ./src/test.cpp ./src/pid_utils.cpp )
