# Udacity Robotics course  - Home Service Robot Project
ARG BASE_TAG=noetic
FROM osrf/ros:${BASE_TAG}-desktop-full

# set shell as non interactive, doesn't stall waiting for user input
ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS="yes"

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# install some utilities
RUN apt-get update && apt-get install -y \
  aptitude \
  vim \
  wget \
  git \
  bash-completion \
  sudo

# install dependencies for turtlebot3
# https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/
RUN apt-get update && apt-get install -y \
  ros-noetic-joy ros-noetic-teleop-twist-joy \
  ros-noetic-teleop-twist-keyboard ros-noetic-laser-proc \
  ros-noetic-rgbd-launch ros-noetic-rosserial-arduino \
  ros-noetic-rosserial-python ros-noetic-rosserial-client \
  ros-noetic-rosserial-msgs ros-noetic-amcl ros-noetic-map-server \
  ros-noetic-move-base ros-noetic-urdf ros-noetic-xacro \
  ros-noetic-compressed-image-transport ros-noetic-rqt* ros-noetic-rviz \
  ros-noetic-gmapping ros-noetic-navigation ros-noetic-interactive-markers 

# install TurtleBot3 packages
RUN apt-get install -y ros-noetic-dynamixel-sdk 
RUN apt-get install -y ros-noetic-turtlebot3-msgs 
RUN apt-get install -y ros-noetic-turtlebot3 

RUN apt-get install -y tmux

ENV TURTLEBOT3_MODEL=burger

RUN rm -rf /var/lib/apt/lists/*
# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
USER $USERNAME

RUN sh -c 'echo "source $HOME/project_five/devel/setup.bash" >> ~/.bashrc'
RUN sh -c 'echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc'
RUN sh -c 'echo "source $HOME/.bashrc" >> ~/.profile'

# entrypoint
COPY ros_entrypoint.sh /usr/local/bin/ros_entrypoint.sh
ENTRYPOINT ["/usr/local/bin/ros_entrypoint.sh"]
CMD [ "bash" ]