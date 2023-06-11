在ROS 2中，默认情况下是不会输出RCLCPP_DEBUG级别的日志的。这是因为在ROS 2的日志系统中，默认的日志级别是INFO，只有INFO级别及以上的日志才会被输出。

要输出RCLCPP_DEBUG级别的日志，你需要进行额外的配置。
通过启动参数指定日志级别：
在启动节点时，可以通过参数--ros-args来指定日志级别。例如，使用以下命令启动节点，并指定日志级别为DEBUG and above：
```bash
ros2 run example_parameters_rclcpp parameters_basic --ros-args --log-level debug -p rcl_log_level:=4
```



