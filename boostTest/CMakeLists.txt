cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)

project(boostTest)

add_executable(boostTestArr
        arrayTESTS.cpp
        classes/arr.cpp
)

add_executable(boostTestHashMap
        hashMapTESTS.cpp
        classes/hashMap.cpp
        classes/list.cpp
        classes/Pair.cpp
        classes/arr.cpp
)

add_executable(boostTestLists
        listTESTS.cpp
        classes/list.cpp
        classes/Pair.cpp
)

add_executable(boostTestQueue
        queueTESTS.cpp
        classes/queue.cpp
)

add_executable(boostTestSCL
        sclTESTS.cpp
        classes/singleConnList.cpp
)

add_executable(boostTestStack
        stackTESTS.cpp
        classes/Stack.cpp
)

add_custom_target(all-tests)
add_dependencies(all-tests boostTestArr boostTestHashMap boostTestLists boostTestQueue boostTestSCL boostTestStack)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")