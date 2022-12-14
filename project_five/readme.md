# Udacity Project "Home Service Robot"

## Workspace Docker Container
There is a problem installing dependencies for the Turtlebot packages in ROS Noetic, so I tried to create a docker container with ROS kinetic, and access to an nvidia gpu and Gazebo (9 or 7). However none of that worked seemlessly, on the udactiy workspace there were expired signatures and in the docker container I couldn't get the realsense dependency installed.  

### TurtleBot3
So instead I am using turtlebot3 and Noetic, ensuring compatibility with `openslam gmapping`.  See `turtlebot3.Dockerfile` then add the following to the src dir
```
cd src
git clone -b noetic-devel https://github.com/ROBOTIS-GIT/turtlebot3
git clone -b noetic-devel https://github.com/ROBOTIS-GIT/turtlebot3_simulations
cd ..
catkin_make
```
Test launch with 
```
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_gazebo turtlebot3_world.launch
```

More information available from:
* https://emanual.robotis.com/docs/en/platform/turtlebot3/simulation/
* https://www.youtube.com/watch?v=ji2kQXgCjeM


```
mkdir -p ~/project_five/src
cd ~/project_five/src
catkin_init_workspace
cd ..
catkin_make
```

### World File
Using the basic ground floor world create for earlier tutorials, with some extra features added from the repo of [gazebo models](https://github.com/osrf/gazebo_models).  These are stored in the  `src/turtlebot3/turtlebot3_gazebo/` `launch`, `models` and `worlds` directories.

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

