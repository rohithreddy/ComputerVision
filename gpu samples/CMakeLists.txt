cmake_minimum_required(VERSION 3.5 )
project( gpuTest )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(  gpuTest gpuTest.cpp )
target_link_libraries( gpuTest ${OpenCV_LIBS})
