cmake_minimum_required(VERSION 3.22.1)
project("aimlock")

# Optimize build (-O3) and hide internal symbols (-fvisibility=hidden)
add_compile_options(
    -O3
    -fvisibility=hidden
    -Wall
    -Wextra
    -std=c++17
)

# Strip all symbols (-s) and exclude unused exported libraries for release hardening
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s -Wl,--exclude-libs,ALL")
endif()

# Build the native shared library (.so)
add_library(aimlock SHARED
    aimlock.cpp
)

# Find Android logging library
find_library(log-lib log)

# Link dependencies
target_link_libraries(aimlock
    PRIVATE
    ${log-lib}
)
