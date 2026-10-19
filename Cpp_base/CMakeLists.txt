cmake_minimum_required(VERSION 4.3)
project(Cpp-repo)

set(CMAKE_CXX_STANDARD 17)

add_executable(base_demo main.cpp)
add_executable(data-types 01-data_types/main.cpp)
# 算术运算符
add_executable(ArithmeticOperators
        02-Operators/ArithmeticOperators/main.cpp
)

# 逻辑运算符
add_executable(logicalOperators
        02-Operators/logicalOperators/main.cpp
)

#程序控制流
add_executable(switch_case 03-programFlow/main.cpp)

#一维数组
add_executable(1d-array 04-array/1DArray/main.cpp)
