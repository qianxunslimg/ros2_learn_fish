# cmake_minimum_required(VERSION 3.10)

# project(first_node)

# #include_directories 添加特定的头文件搜索路径 ，相当于指定g++编译器的-I参数
# include_directories(/opt/ros/foxy/include/)

# # no need for this
# #include_directories(/opt/ros/dashing/include/rclcpp/)
# #include_directories(/opt/ros/dashing/include/rcl/)
# #include_directories(/opt/ros/dashing/include/rcutils/)
# #include_directories(/opt/ros/dashing/include/rcl_yaml_param_parser/)
# #include_directories(/opt/ros/dashing/include/rosidl_runtime_c/)
# #include_directories(/opt/ros/dashing/include/rosidl_typesupport_interface/)
# #include_directories(/opt/ros/dashing/include/rcpputils/)
# #include_directories(/opt/ros/dashing/include/builtin_interfaces/)
# #include_directories(/opt/ros/dashing/include/rmw/)
# #include_directories(/opt/ros/dashing/include/rosidl_runtime_cpp/)
# #include_directories(/opt/ros/dashing/include/tracetools/)
# #include_directories(/opt/ros/dashing/include/libstatistics_collector/)
# #include_directories(/opt/ros/dashing/include/statistics_msgs/)

# # link_directories - 向工程添加多个特定的库文件搜索路径，相当于指定g++编译器的-L参数
# link_directories(/opt/ros/foxy/lib/)

# # add_executable - 生成first_node可执行文件
# add_executable(first_node first_ros2_node.cpp)

# # target_link_libraries - 为first_node(目标) 
# # 添加需要动态链接库，相同于指定g++编译器-l参数
# target_link_libraries(first_node rclcpp rcutils)





cmake_minimum_required(VERSION 3.10)

project(first_node)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(${PROJECT_NAME} first_ros2_node.cpp)

ament_target_dependencies(${PROJECT_NAME} rclcpp)

# this was wrong, because 
# ament_target_dependencies 和 target_link_libraries 的区别在于，
# 前者只适用于使用 find_package 找到的包，而后者适用于本地编译的库。
# 如果你使用的库没有通过 find_package 找到，需要使用 target_link_libraries。
# 使用的是 ROS 2 的库，而 ROS 2 的库通常是通过 find_package 找到的。
#target_link_libraries(${PROJECT_NAME} rclcpp::rclcpp)