cmake_minimum_required(VERSION 3.29)

project(LR_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(LR_1
        structures/arr.cpp
        structures/hashMap.cpp
        structures/list.cpp
        structures/Pair.cpp
        structures/queue.cpp
        structures/singleConnList.cpp
        structures/Stack.cpp
        structures/Set.cpp

        class_func/arr_funcs.cpp
        class_func/generalFuncs.cpp
        class_func/hashMap_funcs.cpp
        class_func/list_funcs.cpp
        class_func/queue_funcs.cpp
        class_func/stack_funcs.cpp
        class_func/set_funcs.cpp

        main.cpp
)