project(spiritoflatex)
cmake_minimum_required(VERSION 3.1)

# C++ Standard and warnings
#set (CMAKE_CXX_STANDARD 14)
if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing ${CMAKE_CXX_FLAGS}")
endif()

# Boost
find_package(Boost REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# Qt (temporary, for checking)
find_package(Qt5Widgets)

FILE(GLOB_RECURSE SRC src/*.c++)
FILE(GLOB_RECURSE INCLUDE include/*.h++)
include_directories(include src)
add_executable(spiritoflatex WIN32 ${SRC} ${INCLUDE} README.md LICENSE)
target_link_libraries(spiritoflatex ${Boost_LIBS} Qt5::Widgets)
