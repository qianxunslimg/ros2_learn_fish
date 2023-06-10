# msg and srv
在ROS 2中，srv和msg都是用于消息传递的文件类型。

msg（Message）文件定义了消息的结构，用于在ROS 2系统中进行数据交换。它们通常用于发布和订阅通信模式，其中节点通过发送和接收消息进行信息传递。msg文件使用一种简单的文本格式进行描述，指定了消息的字段和其数据类型。例如，可以定义一个包含整数和字符串字段的消息类型。

srv（Service）文件定义了服务的结构，服务是一种用于`请求和响应`的通信模式。服务由一个请求消息和一个响应消息组成，客户端节点发送请求消息，服务器节点接收请求并返回响应消息。srv文件也使用类似于msg文件的文本格式进行描述，指定了请求和响应消息的字段和数据类型。
```xml
# 前进后退的距离
float32 distance
---
# 当前的位置
float32 pose
```
使用msg和srv文件可以帮助节点之间进行数据交换和通信。在ROS 2中，你可以通过定义自己的msg和srv文件来创建自定义的消息类型，以满足你的应用程序需求。然后，你可以在代码中使用生成的消息代码，对消息进行填充、发布和订阅，或者发送和接收服务请求和响应。
```xml
uint32 STATUS_MOVEING = 1
uint32 STATUS_STOP = 2
uint32  status
geometry_msgs/Pose pose
```
总结来说，msg文件用于定义消息结构，而srv文件用于定义服务结构。它们都是ROS 2中用于消息传递的重要文件类型，用于在节点之间进行通信和数据交换。

# codeing
In cmakelists should add
```cmake
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED) # if msg use geometry_msgs

# 添加下面的内容
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotPose.msg"
  "msg/RobotStatus.msg"
  "srv/MoveRobot.srv"
  DEPENDENCIES geometry_msgs
)
```