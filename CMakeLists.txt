cmake_minimum_required(VERSION 3.0.2)
project(tas_proj)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(catkin REQUIRED COMPONENTS roscpp roslib)
find_package(Eigen3 REQUIRED)
find_package(Proj REQUIRED)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp
    DEPENDS EIGEN3 PROJ
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${PROJ_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
    src/coordinate_system_converter.cpp
    src/gps_converter.cpp
    src/gps_utm_converter.cpp
    src/geoid_converter.cpp
    src/gps_coord.cpp
    src/utm_coord.cpp
    )

target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${PROJ_LIBRARIES}
    )
