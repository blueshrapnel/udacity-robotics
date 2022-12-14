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
sudo \
ros-noetic-navigation \
ros-noetic-map-server \
ros-noetic-move-base \
ros-noetic-amcl \
ros-noetic-rtabmap-ros \
ros-noetic-rtabmap \
libboost-all-dev \
libignition-math4-dev \
protobuf-compiler \
&& rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y ros-noetic-openslam-gmapping

# ros-noetic-effort-controllers \ # needed for simple_arm

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