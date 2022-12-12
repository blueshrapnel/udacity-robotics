# Turtlebot 2 - Grid Fast Slam


## Lab Walk Through

### setup Ros environment

Starting with the nvidia-kinetic base image install turtlebot 2 packages
* `git clone https://github.com/turtlebot/turtlebot_simulator`
* `git clone https://github.com/turtlebot/turtlebot`

Install Ros dependencies
* update the public key for ROS - may be superfluous
`ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=DontWarn 
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -`
*  setup sources list `RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'`
* include EOL distros, i.e. kinetic `rosdep update --include-eol-distros` 
* install ros dependencies for packages in the workspace `rosdep install --from-paths . -y -r `

Install gmapping$ 
* git clone https://github.com/ros-perception/slam_gmapping
* rosdep install gmapping

### launch packages

Make the project `catkin_make`, sourced, etc, then in separate terminals run the following ros commands:
* `roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=worlds/willowgarage.world`
* `roslaunch turtlebot_teleop keyboard_teleop.launch`
* `rosrun gmapping slam_gmapping`
* `rosrun rviz rviz`
* `rosrun map_server map_server -f myMap`

## Observations
Map does not disregard the teleop commands when the robot is bumping into an obstacle.