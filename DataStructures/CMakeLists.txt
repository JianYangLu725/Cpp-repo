cmake_minimum_required(VERSION 4.3)
project(Cpp_repo)

set(CMAKE_CXX_STANDARD 17)

add_executable(sequentialList 01-SequentialList/main.cpp)
add_executable(LinkedList 02-LinkedList/main.cpp)
add_executable(seqStack 03-Stack/v-SeqList/main.cpp)
add_executable(linkStack 03-Stack/v-LinkList/main.cpp)
add_executable(SeqQueue 04-Queue/v-SeqList/main.cpp)
add_executable(LinkedQueue 04-Queue/v-LinkedList/main.cpp)
add_executable(Stk2Queue 04-Queue/v-Stack2Queue/main.cpp)
add_executable(Queue2Stk 03-Stack/v-Queue2Stack/main.cpp)