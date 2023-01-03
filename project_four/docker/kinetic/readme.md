# Docker Container for ROS Kinetic

Summary of experiences creating a docker container for ROS kinetic with a working Gazebo simulation.  There are two options, start from the ROS kinetic-full-desktop container, or from the nvidia cuda container, either `nvidia/cudagl:9.0-base-ubuntu16.04` or `nvidia/cudagl:10.0-devel-ubuntu16.04`.

## Starting from ROS container
ROS kinetic installs without any issues, however running Gazebo fails as it lacks
the OpenGL pieces required to make the visualization applications work. Also, the default gazebo version with `ros:kinetic-desktop-full-xenial` is version 7, which is particularly poor in terms of window management.

## Starting from Nvidia container
This has the benefit of having the nvidia drivers working in advance of installing Gazebo.  With the option of installing ROS kinetic and then a more recent version of gazebo: [official sources](http://gazebosim.org/tutorials?cat=install&tut=install_ubuntu&ver=7.0).

## Gazebo
After trying to update gazebo from 7 to 9 in the docker file in the dockerfile, it works but then the turtlebot package dependencies are not met.  So going back to installing Gazebo 7 via the `...-dektop-full` package.
``` 
# update public key for gazebo
ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=DontWarn 
RUN sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN curl --insecure https://packages.osrfoundation.org/gazebo.key | sudo apt-key add -

RUN sudo apt-get remove ros-kinetic-gazebo* -y

RUN apt-get update && apt-get install -y \
ros-kinetic-gazebo9-ros-pkgs \
ros-kinetic-gazebo9-ros-control ros-kinetic-gazebo9* 

```
## Building container
Build docker container with 
`docker build -t roomba -f docker/nvidia-kinetic.Dockerfile docker/.`

Trying to add files while building docker image, then `docker build -t simple-roomba -f docker/kinetic.Dockerfile .` - note the context of the build command needs to be compatible with the commands below.
```
# add directory
WORKDIR /home/ros/project_five
COPY . /home/ros/project_five
RUN sh -c 'pwd && ls'
RUN bash -c 'source /opt/ros/kinetic/setup.bash'
RUN bash -c 'source devel/setup.bash'
RUN sudo rosdep init
RUN rosdep update --include-eol-distros
RUN rosdep install -i gmapping # can't get this to work
```

Another option is to add all this specific ros config stuff to the entrypoint.

## Running container

    * remember to run xhost +local:[marlyn]
    * source='/home/karen/workspace/udacity-robotics' && target='/home/ros/'

```
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
```

## 