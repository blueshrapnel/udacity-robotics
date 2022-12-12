#!/bin/bash

echo " ---> sourcing /opt/ros/kinetic/setup.bash"
source "/opt/ros/kinetic/setup.bash"
# working directory must be a catkin workspace
echo " ---> sourcing devel/setup.bash"
source "devel/setup.bash"
exec "$@"