# comment
## run the node with param
```bash
ros2 run param_demo par_demo --ros-args -p my_param:=hello
```
当你运行ros2 run param_demo par_demo命令时，你正在启动名为param_demo的ROS 2节点。

--ros-args选项允许你向ROS 2节点传递额外的参数。在这个命令中，我们将使用-p选项来设置一个启动参数。

-p my_param:=hello这部分表示要设置一个参数，参数名为my_param，参数值为hello。注意，我们使用:=来分配参数值。

综上所述，整个命令ros2 run param_demo par_demo --ros-args -p my_param:=hello的含义是：运行名为param_demo的ROS 2节点，并将参数my_param的值设置为hello。这样，你的节点在运行时会使用这个设置的参数值。

## launch the node with param
use map to load param
```py
## style 1
# import launch
# import launch_ros.actions

# def generate_launch_description():
#     parameters = [
#         {"my_param": "hello"}
#     ]

#     node = launch_ros.actions.Node(
#         package='param_demo',
#         executable='par_demo',
#         output='screen',
#         parameters=parameters
#     )

#     return launch.LaunchDescription([node])

# if __name__ == '__main__':
#     generate_launch_description()

# style 2
import os
from launch import LaunchDescription
from launch_ros.actions import Node  #foxy and galactic
#from launch_ros.actions import Node  #other ros
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    parameters = [
        {"my_param": "hello"}
    ]

    node = Node(
        package='param_demo',
        executable='par_demo',
        output='screen',
        parameters=parameters
    )

    return LaunchDescription([node])
```