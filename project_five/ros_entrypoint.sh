#!/bin/bash
echo "current directory: $PWD"
echo " ---> sourcing /opt/ros/noetic/setup.bash"
source "/opt/ros/noetic/setup.bash"
# working directory must be a catkin workspace
if [ -d "devel" ]
then 
    catkin_make
    echo " ---> sourcing devel/setup.bash"
    source "devel/setup.bash"
fi
exec "$@"