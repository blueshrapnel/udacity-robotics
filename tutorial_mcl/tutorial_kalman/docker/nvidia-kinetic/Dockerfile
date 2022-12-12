# Udacity Robotics course 

FROM nvidia/cudagl:10.0-devel-ubuntu16.04

#  Minimal setup
RUN apt-get update \
 && apt-get install -y locales lsb-release
ARG DEBIAN_FRONTEND=noninteractive
RUN dpkg-reconfigure locales

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics


# install some utilities
RUN apt-get update && apt-get install -y \
vim \
wget \
curl \
git \
bash-completion \
sudo \
&& rm -rf /var/lib/apt/lists/*

# setup sources list
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

# update the public key for ROS - may be superfluous
ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=DontWarn 
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

# install ROS Kinetic http://wiki.ros.org/kinetic/Installation/Ubuntu
RUN sudo apt-get update && apt-get install ros-kinetic-desktop-full -y
# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
RUN sh -c 'echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc'
USER $USERNAME

RUN sudo rosdep init
RUN rosdep update --include-eol-distros
RUN rosdep fix-permissions

# WORKDIR /home/ros/tutorial_kalman/kinetic/
# git clone https://github.com/turtlebot/gazebo_simulation into src
# need to source /opt/ros/kinetic/setup.bash
# need to source devel/setup.bash
# RUN sudo apt-get update && pwd && rosdep install --from-paths . -y -r 

# entrypoint
# ENTRYPOINT ["/ros_entrypoint.sh"]
CMD [ "bash" ]
