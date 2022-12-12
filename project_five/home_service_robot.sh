#! /bin/bash

# remember to run xhost +local:[marlyn]

# source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

# in same directory as Dockerfile, docker build -t kinetic-roomba .
source='/home/karen/workspace/udacity-robotics/project_five' && target='/home/ros/project_five'

docker run -it \
    --gpus all \
    --env="NVIDIA_DRIVER_CAPABILITIES=all" \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --mount type=bind,source=$source,target=$target \
    --workdir="/home/ros/project_five" \
    --privileged \
    --net=host \
    roomba \
    bash
 
