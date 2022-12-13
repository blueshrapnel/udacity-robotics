#!/bin/bash

source devel/setup.bash
source /opt/ros/kinetic/setup.bash

# deploy turtlebot in corridor-world environment for testing
xterm -fa 'Monospace' -fs 14 -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world" &
sleep 15

# gmapping demo

xterm -fa 'Monospace' -fs 14 -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 10


xterm -fa 'Monospace' -fs 14 -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5


xterm -fa 'Monospace' -fs 14 -e "roslaunch turtlebot_teleop keyboard_teleop.launch"