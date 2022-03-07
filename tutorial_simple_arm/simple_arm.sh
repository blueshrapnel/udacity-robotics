#! /bin/bash

# source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

# docker build -t noetic .
# added sudo apt install 

source='/home/karen/workspace/udacity-robotics' && target='/home/ros'

docker run -it \
    --gpus all \
    --env="NVIDIA_DRIVER_CAPABILITIES=all" \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --mount type=bind,source=$source,target=$target \
    --workdir="/home/ros/tutorial_simple_arm" \
    --privileged \
    --net=host \
    noetic \
    bash
