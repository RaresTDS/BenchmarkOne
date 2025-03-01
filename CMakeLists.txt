cmake_minimum_required(VERSION 3.27)
project(Benchmark_One)

set(CMAKE_CXX_STANDARD 17)

# Găsește GTK folosind pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Include directoarele de antet GTK
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

# Creează executabilul și linkează librăriile GTK
add_executable(Benchmark_One main.cpp)
target_link_libraries(Benchmark_One ${GTK_LIBRARIES})
