#!/bin/sh
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../World/my_world.world " &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../World/my_world1.yaml" &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch home-service-robot view_navigation.launch" &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; rosrun add_markers add_markers_node" &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; rosrun pick_objects pick_objects_node" &
