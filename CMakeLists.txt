cmake_minimum_required(VERSION 3.10)
project(WebScraper)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the libcurl package
find_package(CURL REQUIRED)

# Include the libcurl headers
include_directories(${CURL_INCLUDE_DIR})

# Add the executable target
add_executable(WebScraper main.cpp)

# Link the executable with libcurl
target_link_libraries(WebScraper ${CURL_LIBRARIES})
