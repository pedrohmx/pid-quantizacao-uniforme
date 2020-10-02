# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( pid-rgb2gray )

# flags

# include
include_directories( ./src )

#target
add_executable( rgb2gray  ./src/main.cpp )

