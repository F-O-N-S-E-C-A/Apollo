#!/bin/bash

#https://github.com/henry2423/docker-ros-x11
xhost +local: 
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
touch $XAUTH
xauth add $(hostname)/unix:${DISPLAY#*:} MIT-MAGIC-COOKIE-1 $(xxd -l 16 -p /dev/urandom)

sudo docker run -it \
  --volume /tmp/.X11-unix:/tmp/.X11-unix:rw \
  --volume /tmp/.docker.xauth:/tmp/.docker.xauth:rw \
  --env "XAUTHORITY=/tmp/.docker.xauth" \
  --env "DISPLAY" \
  --volume /etc/passwd:/etc/passwd \
  --volume /etc/group:/etc/group \
  --volume /home/apollo/Apollo/sim/docker_container_vol_data:/data:rw \
  --user root \
  --gpus all \
  apollo:v1.0 \
  bash

