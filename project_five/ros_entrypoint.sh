#!/bin/bash
echo "current directory: $PWD"
echo " ---> sourcing /opt/ros/kinetic/setup.bash"
source "/opt/ros/kinetic/setup.bash"
# working directory must be a catkin workspace
echo " ---> sourcing devel/setup.bash"
source "devel/setup.bash"

echo " ---> installing gmapping"
rosdep install -y gmapping 
echo " ---> installing turtlebot_teleop"
rosdep install -y turtlebot_teleop
echo " ---> installing turtlebot_rviz_launchers"
rosdep install -y turtlebot_rviz_launchers
echo " ---> installing turtlebot_gazebo"
rosdep install -y turtlebot_gazebo
echo " ---> running cmake.... "
catkin_make
echo " ---> sourcing /opt/ros/kinetic/setup.bash"
source "/opt/ros/kinetic/setup.bash"
# working directory must be a catkin workspace
echo " ---> sourcing devel/setup.bash"
source "devel/setup.bash"
exec "$@"