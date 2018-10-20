#!/bin/sh
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/home_service_robot_ws/src/World/my_world.world " &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch gmapping gmapping_demo.launch" &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm -e "cd $(pwd)/../..; source devel/setup.bash ; rosrun wall_follower wall_follower" &
