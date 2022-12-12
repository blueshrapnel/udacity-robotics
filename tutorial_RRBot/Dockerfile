# Udacity Robotics course 

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
RUN apt-get update && apt-get install -y apt-utils

RUN apt-get install -y vim \
wget \
git \
bash-completion \
sudo \
ros-noetic-robot-state-publisher \
&& rm -rf /var/lib/apt/lists/*


# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
USER $USERNAME

RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc

# entrypoint
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD [ "bash" ]
