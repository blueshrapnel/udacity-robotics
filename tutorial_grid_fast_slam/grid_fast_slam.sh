#! /bin/bash

# source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

# To get turtlebot 2 to work with the packages used for this lab
# ROL kinetic is required.  Start from nvidia-kinetic docker img
# docker build -t kinetic-slam ./nvidia-kinetic/.

# $ git clone https://github.com/turtlebot/turtlebot_simulator
# $ git clone https://github.com/turtlebot/turtlebot
# $ rosdep install --from-paths . -y -r 

source='/home/karen/workspace/udacity-robotics' && target='/home/ros'


# https://stackoverflow.com/questions/35067711/start-and-attach-a-docker-container-with-x11-forwarding
# remember to run xhost +local:[marlyn]

docker run -it \
    --gpus all \
    --env="NVIDIA_DRIVER_CAPABILITIES=all" \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --mount type=bind,source=$source,target=$target \
    --workdir="/home/ros/tutorial_grid_fast_slam" \
    --privileged \
    --net=host \
    kinetic-slam \
    bash
