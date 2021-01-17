cmake_minimum_required(VERSION 3.5)

project(TestTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "C:\\OpenCV\\build")
FIND_PACKAGE( OpenCV REQUIRED )

add_executable(TestTask main.cpp)

TARGET_LINK_LIBRARIES (TestTask ${OpenCV_LIBS})