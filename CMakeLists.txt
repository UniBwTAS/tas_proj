cmake_minimum_required(VERSION 3.8)
project(tas_proj)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Proj REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
    src/coordinate_system_converter.cpp
    src/gps_converter.cpp
    src/gps_utm_converter.cpp
    src/geoid_converter.cpp
    src/gps_coord.cpp
    src/utm_coord.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>")
target_link_libraries(${PROJECT_NAME} ${PROJ_LIBRARIES})
ament_target_dependencies(${PROJECT_NAME} rclcpp)

# Install rules
install(TARGETS ${PROJECT_NAME}
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})

install(DIRECTORY media cmake DESTINATION share/${PROJECT_NAME})

# Export old-style CMake variables
ament_export_include_directories("include/${PROJECT_NAME}")
ament_export_libraries(${PROJECT_NAME})

# Export modern CMake targets
ament_export_targets(export_${PROJECT_NAME})

ament_export_dependencies(rclcpp)
ament_export_dependencies(PROJ)

ament_package(CONFIG_EXTRAS tas_proj-extras.cmake)