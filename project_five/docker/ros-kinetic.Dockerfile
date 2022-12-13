# Udacity Robotics course 
# Doesn't work with gazebo - needs open gl etc
# use nvidia-kinetic.Dockerfile

ARG BASE_TAG=kinetic
FROM osrf/ros:${BASE_TAG}-desktop-full

# set shell as non interactive, doesn't stall waiting for user input
ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS="yes"

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics


# eliminate debconf warnings
RUN apt-get update && apt-get install -y dialog apt-utils

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



# running gazebo swrast not found
RUN apt-get install -y mesa-utils libgl1-mesa-glx

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


