cmake_minimum_required(VERSION 3.29)
project(groq_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(/nlohmann)
link_libraries(cpr)
add_executable(groq_cpp
        nlohmann/json.hpp
        groqapi.cpp
        groqapi.hpp
)
