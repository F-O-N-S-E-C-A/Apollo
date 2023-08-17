# This Dockerfile is used to build an ROS + OpenGL + Gazebo + Tensorflow image based on Ubuntu 18.04
# Based on the work by Henry Huang at https://github.com/henry2423
FROM nvidia/cudagl:11.4.2-devel-ubuntu18.04

LABEL maintainer "Tiago Fonseca"
MAINTAINER Tiago Fonseca "https://github.com/F-O-N-S-E-C-A"
ENV REFRESHED_AT 2023-07-24

# Install sudo
RUN apt-get update && \
    apt-get install -y sudo curl

# Environment config
ENV DEBIAN_FRONTEND=noninteractive

# Add new sudo user
ARG user=ros
ARG passwd=ros
ARG uid=1000
ARG gid=1000
ENV USER=$user
ENV PASSWD=$passwd
ENV UID=$uid
ENV GID=$gid
RUN useradd --create-home -m $USER && \
        echo "$USER:$PASSWD" | chpasswd && \
        usermod --shell /bin/bash $USER && \
        usermod -aG sudo $USER && \
        echo "$USER ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/$USER && \
        chmod 0440 /etc/sudoers.d/$USER && \
        # Replace 1000 with your user/group id
        usermod  --uid $UID $USER && \
        groupmod --gid $GID $USER


### ROS and Gazebo Installation
# Install other utilities
RUN apt-get update && \
    apt-get install -y vim \
    tmux \
    git \
    wget \
    lsb-release \
    lsb-core

# Install ROS and rosdep
RUN curl http://repo.ros2.org/repos.key | sudo apt-key add -
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list' && \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116 && \
    apt-get update && \
    apt-get install -y ros-melodic-desktop && \
    apt-get install -y python-rosdep

# Initialize rosdep
RUN rosdep init

# Install Gazebo 9 and its development libraries
RUN sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list' \
     && wget https://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - \
     && sudo apt-get update -qq \
     && sudo apt-get install gazebo9 libgazebo9-dev -y

# Install Gazebo ROS packages for Melodic
RUN apt-get install -y ros-melodic-gazebo-ros ros-melodic-gazebo-ros-control

# Setup ROS
USER $USER
RUN rosdep fix-permissions && rosdep update
RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"


###Tensorflow Installation
# Install pip
USER root
RUN apt-get install -y wget python3-pip python3-dev libgtk2.0-0 unzip libblas-dev liblapack-dev libhdf5-dev
    #curl https://bootstrap.pypa.io/pip/3.6/get-pip.py -o get-pip.py && \
    #python3 get-pip.py

# prepare default python 3.8 environment
USER root
RUN  pip3 install protobuf==3.19.6 tensorflow keras matplotlib pandas scipy h5py testresources scikit-learn catkin_pkg

RUN apt-get install -y python-catkin-tools
RUN apt-get install -y nano
RUN apt-get install -y ros-melodic-joint-state-controller
RUN apt-get install -y ros-melodic-effort-controllers
RUN apt-get install -y ros-melodic-velocity-controllers
RUN apt-get install -y ros-melodic-position-controllers
RUN apt-get install -y tree
RUN apt-get install -y ros-melodic-gazebo-ros-pkgs

RUN rosdep update

# Expose Jupyter 
EXPOSE 8888

# Expose Tensorboard
EXPOSE 6006

### Switch to root user to install additional software
USER $USER
