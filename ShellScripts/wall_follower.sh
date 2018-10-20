#!/bin/sh
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/robond/home_robot_ws/src/World/my_world.world " &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; rosrun gmapping gmapping_demo.launch" &
sleep 5
xterm  -e "cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm -e "cd $(pwd)/../..; source devel/setup.bash ; rosrun wall_follower wall_follower" &
