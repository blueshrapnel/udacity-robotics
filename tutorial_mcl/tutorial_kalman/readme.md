# Turtlebot 2

This took a long time to get working, trying several attempts, see below for some noteworthy failures.  Final solution was rebuild starting with nvidia image.

I tried to automate installing the `gazebo_simulator` packages and running rosdep, but I wasn't able to get the paths sorted correctly.

## ros dependencies
Lessons learned regarding successfully using `rosdep`
*  setup sources list
`RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'`

* update the public key for ROS - may be superfluous
`ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=DontWarn 
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -`

* more details here install ROS Kinetic http://wiki.ros.org/kinetic/Installation/Ubuntu

* `apt-get update` - if you change the sources, keys, anything, just update
* `rosdep init`
* `rosdep update --include-eol-distros` 
* `rosdep install --from-paths src  -r -y`, note you can specify `--rosdistro=kinetic` but  unnecessary in the end

## failures
* https://github.com/gaunthan/Turtlebot2-On-Melodic - ecl packages then have unkown build types which prevents catkin_make from completing
* kinetic xenial nvidia - managed to get it to install after some tweaking, but didn't launch successfully
* melodic bionic (problem with turtlebot_navigation)
* osfr kinetic desktop full requires xenial - nvidia libgl doesn't work so can't run gazebo gui, tried to install `mesa-utils` and `libgl1-mesa-glx`



