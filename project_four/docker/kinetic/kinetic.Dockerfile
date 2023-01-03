# Udacity Robotics course 

FROM nvidia/cudagl:10.0-devel-ubuntu16.04

# set shell as non interactive, doesn't stall waiting for user input
ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS="yes"

# install some utilities
RUN apt-get update && apt-get install -y \
aptitude \
vim \
wget \
git \
bash-completion \
sudo \
&& rm -rf /var/lib/apt/lists/*

# Register the ROS package sources.
# http://wiki.ros.org/kinetic/Installation/Ubuntu
ENV UBUNTU_RELEASE=xenial
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $UBUNTU_RELEASE main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

# issues with GPG signatures
# as per https://github.com/NVIDIA/nvidia-docker/issues/1632#issuecomment-1112667716
RUN rm /etc/apt/sources.list.d/cuda.list
RUN rm /etc/apt/sources.list.d/nvidia-ml.list

# Install ROS with Gazebo
# Note:  ros-kinetic-turtlebot-gazebo : Depends: ros-kinetic-gazebo-ros
#                                       Depends: ros-kinetic-kobuki-gazebo-plugins
RUN apt-get update && apt-get install -y \
    ros-kinetic-desktop-full \
    && rm -rf /var/lib/apt/lists/*

# Add osrfoundation repo https://classic.gazebosim.org/tutorials?tut=install_ubuntu&cat=install
# as we can't install gazebo 9, then at least upgrade to 7.16
RUN sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
RUN apt-get update
RUN apt-get --with-new-pkgs upgrade -y

RUN sudo rosdep init

# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
USER $USERNAME

RUN rosdep update --include-eol-distros

# entrypoint
COPY ros_entrypoint.sh /usr/local/bin/ros_entrypoint.sh
ENTRYPOINT ["/usr/local/bin/ros_entrypoint.sh"]
CMD [ "bash" ]