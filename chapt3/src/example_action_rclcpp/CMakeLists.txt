cmake_minimum_required(VERSION 3.5)
project(example_action_rclcpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

################################################################
#add for solve clion debug due to can not find the so of interface
link_directories(/home/qianxunslimg/Desktop/suudy/ros_study/d2lros2/chapt4/build/robot_control_interfaces)
include_directories(/home/qianxunslimg/Desktop/suudy/ros_study/d2lros2/chapt4/build/robot_control_interfaces/rosidl_generator_cpp)
################################################################

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(robot_control_interfaces REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rclcpp_action REQUIRED)

# action_robot节点

add_executable(action_robot_01
        src/robot.cpp
        src/action_robot_01.cpp
        )
target_include_directories(action_robot_01 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_compile_features(action_robot_01 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
        action_robot_01
        "rclcpp"
        "rclcpp_action"
        "robot_control_interfaces"
        "example_interfaces"
)

install(TARGETS action_robot_01
        DESTINATION lib/${PROJECT_NAME})

# action_control节点

add_executable(action_control_01
        src/action_control_01.cpp
        )
target_include_directories(action_control_01 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_compile_features(action_control_01 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
        action_control_01
        "rclcpp"
        "rclcpp_action"
        "robot_control_interfaces"
        "example_interfaces"
)

install(TARGETS action_control_01
        DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
