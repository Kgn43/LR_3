cmake_minimum_required(VERSION 3.29)

project(LR_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(LR_1
        classes/arr.cpp
        classes/hashMap.cpp
        classes/list.cpp
        classes/Pair.cpp
        classes/queue.cpp
        classes/singleConnList.cpp
        classes/Stack.cpp
        classes/Set.cpp

        class_func/arr_funcs.cpp
        class_func/generalFuncs.cpp
        class_func/hashMap_funcs.cpp
        class_func/list_funcs.cpp
        class_func/queue_funcs.cpp
        class_func/stack_funcs.cpp
        class_func/set_funcs.cpp

        main.cpp
)