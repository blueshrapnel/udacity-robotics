# Udacity Project "Home Service Robot"

## Workspace Docker Container
There is a problem installing dependencies for the Turtlebot packages in ROS Noetic, so downgrading to ROS Kinetic. :-(
See the `readme.md` in the docker directory for comments on building a container with ROS kinetic, access to nvidia gpu and Gazebo.  Note I tried to update Gazebo to a higher version, however turtlebot has  
In a docker container (see docker.Dockerfile, `docker build -t roomba .`), initialise the workspace as explained below.

```
mkdir -p ~/project_five/src
cd ~/project_five/src
catkin_init_workspace
cd ..
catkin_make
```

```
sudo apt update
cd ~/project_five/src
git clone https://github.com/ros-perception/slam_gmapping
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator

```
The `rosdep` package manager tries to install packages that are part of turtlebot which we do not need, so instead of running the following:
```
sudo rosdep init
rosdep update --include-eol-distros
rosdep install --from-paths src -y -r
```
Only install the necessary components with the following:
```
# install a few more dependencies
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
``` 
The change to the project workspace `project_five` and run `catkin_make`, then`source devel\setup.bash` etc.

## Launching Turtlebot world

Using the corridor world that comes with `turtlebot_simulator`.  To open `xterm` with a default font and size: `xterm -fa 'Monospace' -fs 14`. Testing SLAM in the `turtlebot_simulation/corridor_world`:
![](screen-shots/gazebo-corridor-world.png)

* `roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world`
* `roslaunch turtlebot_gazebo gmapping_demo.launch`
* `roslaunch turtlebot_rviz_launchers view_navigation.launch`

