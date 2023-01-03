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

# Install ROS without Gazebo
RUN apt-get update && apt-get install -y \
    ros-kinetic-desktop \
 && rm -rf /var/lib/apt/lists/*


# Install Gazebo
#  ros-kinetic-turtlebot-gazebo : Depends: ros-kinetic-gazebo-ros but it is not going to be installed
#                                 Depends: ros-kinetic-kobuki-gazebo-plugins but it is not going to be installed


# Add osrfoundation repo
RUN sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
RUN apt-get update

RUN apt-get install -y \
ros-kinetic-gazebo9-ros-pkgs \
ros-kinetic-gazebo9-ros-control \
ros-kinetic-gazebo9*

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

# entrypoint
COPY ros_entrypoint.sh /usr/local/bin/ros_entrypoint.sh
ENTRYPOINT ["/usr/local/bin/ros_entrypoint.sh"]
CMD [ "bash" ]


