cmake_minimum_required(VERSION 3.10)
project(LoggerDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(logger_demo
    src/main.cpp
    src/LoggerManager.cpp
    src/ConsoleLogger.cpp
    src/FileLogger.cpp
)

target_include_directories(logger_demo PUBLIC src)

# Link the executable with the pthread library
target_link_libraries(logger_demo PRIVATE pthread)

set_property(TARGET logger_demo PROPERTY CXX_EXTENSIONS OFF)