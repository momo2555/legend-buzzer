cmake_minimum_required (VERSION 3.0)

project(bridge)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/websocketpp)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/serialib)

set(SRC src/main.cpp src/serialportInterface.cpp src/websocketInterface.cpp)
set(HEADER include/serialportInterface.h include/websocketInterface.h)

add_executable(bridge ${SRC})

target_include_directories(bridge PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/websocketpp)
target_include_directories(bridge PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/serialib/lib)
target_include_directories(bridge PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(bridge INTERFACE Boost::system Boost::thread Boost::regex)

target_link_libraries(bridge PRIVATE serialib)

find_package(Threads REQUIRED)
target_link_libraries(bridge PRIVATE Threads::Threads)