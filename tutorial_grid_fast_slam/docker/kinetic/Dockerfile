# Udacity Robotics course 

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


# install some utilities
RUN apt-get update && apt-get install -y \
vim \
wget \
curl \
git \
bash-completion \
sudo \
# mesa-utils \
# libgl1-mesa-glx \
# dbus \
&& rm -rf /var/lib/apt/lists/*



# update the public key for ROS - may be superfluous
# ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=DontWarn 
# RUN curl -s https://raw.githubusercontent.com/ros/# rosdistro/master/ros.asc | sudo apt-key add -

# install rqt_multiplot
# RUN apt-get update && apt-get install -y \
# ros-kinetic-rqt \
# ros-kinetic-rqt-multiplot \
# libqwt-dev

# create a user that shares the same rights as the host
ARG USERNAME=ros
RUN groupadd $USERNAME
RUN useradd -ms /bin/bash -g $USERNAME $USERNAME
RUN sh -c 'echo "$USERNAME ALL=(root) NOPASSWD:ALL" >> /etc/sudoers'
USER $USERNAME

RUN rosdep update --include-eol-distros
RUN rosdep fix-permissions

WORKDIR /home/ros/tutorial_kalman/kinetic/src/
# need to source devel/setup.bash
# RUN sudo apt-get update && pwd && rosdep install --from-paths . -y -r 

# entrypoint
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD [ "bash" ]
