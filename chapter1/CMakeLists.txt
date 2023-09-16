project(chapter1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fmodules-ts")

add_executable(chapter1
        employee.cpp
        main.cpp
        attribute.cpp)