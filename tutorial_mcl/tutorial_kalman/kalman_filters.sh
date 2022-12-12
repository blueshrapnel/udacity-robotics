#! /bin/bash

# source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

# docker build -t kinetic .

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
    --workdir="/home/ros/tutorial_kalman/catkin_ws" \
    --privileged \
    --net=host \
    $1 \
    bash
