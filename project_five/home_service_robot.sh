#! /bin/bash

# check for optional flag specifying docker image name
# set default imagename
imagename="noetic-roomba" 
while getopts i: flag
do
    case "${flag}" in
        i) imagename=${OPTARG};;
    esac
done
# remember to run xhost +local:[marlyn]

# source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

# in project home director, `docker build -t kinetic-roomba -f .Dockerfile`
source='/home/karen/learning/udacity-robotics/project_five' && target='/home/ros/project_five'

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
    ${imagename} \
    bash
 
