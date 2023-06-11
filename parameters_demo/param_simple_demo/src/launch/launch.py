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