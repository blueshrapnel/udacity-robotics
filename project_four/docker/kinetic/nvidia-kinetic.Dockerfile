# Udacity Robotics course 
# Home Service Robot Project
# gazebo errors

ARG BASE_TAG=kinetic
# FROM osrf/ros:${BASE_TAG}-desktop-full
FROM nvidia/cudagl:10.0-devel-ubuntu16.04

# set shell as non interactive, doesn't stall waiting for user input
ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS="yes"

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# issues with GPG signatures
# as per https://github.com/NVIDIA/nvidia-docker/issues/1632#issuecomment-1112667716
RUN rm /etc/apt/sources.list.d/cuda.list
RUN rm /etc/apt/sources.list.d/nvidia-ml.list

#  Minimal setup
RUN apt-get update \
 && apt-get install -y locales lsb-release
RUN dpkg-reconfigure locales

# eliminate debconf warnings
RUN apt-get install -y dialog apt-utils


# install some utilities
RUN apt-get install -y \
aptitude \
vim \
wget \
git \
bash-completion \
xterm \
sudo \
&& rm -rf /var/lib/apt/lists/*

RUN apt-get update

# Register the ROS package sources.
# http://wiki.ros.org/kinetic/Installation/Ubuntu
ENV UBUNTU_RELEASE=xenial
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $UBUNTU_RELEASE main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

# Install ROS with Gazebo
# Note:  ros-kinetic-turtlebot-gazebo : Depends: ros-kinetic-gazebo-ros
#                                       Depends: ros-kinetic-kobuki-gazebo-plugins
RUN apt-get update && apt-get install -y \
    ros-kinetic-desktop-full \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update

# Install openslam-gmapping and turtlebot
RUN apt-get install -y \
ros-kinetic-openslam-gmapping \
ros-kinetic-librealsense \
ros-kinetic-turtlebot-*

RUN apt-get update && apt-get upgrade -y

# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
USER $USERNAME

RUN sudo rosdep init
RUN rosdep update --include-eol-distros

# entrypoint
COPY ros_entrypoint.sh /usr/local/bin/ros_entrypoint.sh
ENTRYPOINT ["/usr/local/bin/ros_entrypoint.sh"]
CMD [ "bash" ]


