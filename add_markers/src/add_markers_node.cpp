#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

class AddMarker
{
private:
  ros::NodeHandle n;
  ros::Publisher marker_pub;
  ros::Subscriber odom_sub;
  visualization_msgs::Marker marker;
  double start_goal[2] = {2.94, 6.13};
  double end_goal[2] = {-4.26, 6.22};

public:
  AddMarker() {
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    odom_sub = n.subscribe("/odom", 1, &AddMarker::odomCallback, this);
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers_node";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::CUBE;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = start_goal[0];
    marker.pose.position.y = start_goal[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    
  }
  void odomCallback(const nav_msgs::Odometry::ConstPtr &msg) {
    float x_pos             = msg->pose.pose.position.x;
    float y_pos             = msg->pose.pose.position.y;
    float x_scale           = marker.scale.x;
    float y_scale           = marker.scale.y;
    bool reached_start_goal = false;
    bool reached_end_goal   = false;


    if ((x_pos < (start_goal[0] + x_scale)) && (x_pos > (start_goal[0] - x_scale)) && (y_pos < (start_goal[1] + y_scale)) && (y_pos > (start_goal[1] - y_scale))) {
      reached_start_goal = true;
      ROS_INFO("Reached Start Goal");
      ROS_INFO("Waiting 5 seconds to simulate pickup");
      ros::Duration(5).sleep();

      marker.action = visualization_msgs::Marker::DELETE;
      ROS_INFO("Removing object");
      marker_pub.publish(marker);    
    }
    else if ((x_pos < (end_goal[0] + x_scale)) && (x_pos > (end_goal[0] - x_scale)) && (y_pos < (end_goal[1] + y_scale)) && (y_pos > (end_goal[1] - y_scale))) {
        reached_end_goal = true;
        ROS_INFO("Reached End Goal");
        ROS_INFO("Waiting 2 seconds to simulate dropoff");
        ros::Duration(2).sleep();

        marker.pose.position.x = end_goal[0];
        marker.pose.position.y = end_goal[1];
        marker.action = visualization_msgs::Marker::ADD;

        marker_pub.publish(marker);
        
      }
    }
};


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_node");
  
  AddMarker addMarker;
  ros::spin();

  return 0; 
}
