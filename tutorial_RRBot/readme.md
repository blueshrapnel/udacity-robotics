# RRBot Tutorial

RRBot is a revolute-revolute manipulator robot, see the [gazebo urdf tutorial](http://gazebosim.org/tutorials/?tut=ros_urdf) for details.

```shell
cd ~/catkin_ws/src/
git clone https://github.com/ros-simulation/gazebo_ros_demos.git
cd ..
catkin_make
```

## Bugs
edit rrbot_rviz.launch and change `type="state_publisher"` to `type="robot_state_publisher`, see [answers.ros](https://answers.ros.org/question/357672/cannot-locate-node-of-type-state_publisher/).