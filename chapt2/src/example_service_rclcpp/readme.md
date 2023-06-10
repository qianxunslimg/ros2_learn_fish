# the command line of service
对于ROS 2的服务，以下是一些常用的命令行工具：

ros2 service list：列出当前所有可用的服务。该命令将显示服务的名称。

ros2 service type <service_name>：查看特定服务的类型。将<service_name>替换为实际的服务名称。

ros2 interface show <service_type>：显示给定服务类型的接口定义。将<service_type>替换为实际的服务类型。

ros2 service call <service_name> <service_type> <request>：通过命令行调用服务并发送请求。将<service_name>替换为实际的服务名称，<service_type>替换为实际的服务类型，<request>替换为实际的请求数据。例如：

```bash
ros2 service call /my_add_two_ints_service example_interfaces/srv/AddTwoInts "{a: 10, b: 20}"
```
这将调用名为/my_add_two_ints_service的服务，使用example_interfaces/srv/AddTwoInts作为服务类型，并发送一个请求"{a: 10, b: 20}"。

ros2 service info <service_name>：显示特定服务的详细信息，包括服务节点的名称、类型和可用的请求和响应消息类型。

这些命令可帮助您在命令行中查看和操作ROS 2的服务。对于特定的服务，请将<service_name>和<service_type>替换为实际的值。请注意，<service_type>是服务的接口类型，通常以.srv文件扩展名表示。

# the coding of service
```c++
rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_ = this->create_client<example_interfaces::srv::AddTwoInts>("my_add_two_ints_service");

rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_server_ =
            this->create_service<example_interfaces::srv::AddTwoInts>("my_add_two_ints_service",
            std::bind(&ServiceServer01::handle_add_two_ints, this, std::placeholders::_1, std::placeholders::_2));
```


