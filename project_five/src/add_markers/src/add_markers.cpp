#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib_msgs/GoalID.h>

// double poseAMCLx, poseAMCLy, poseAMCLw;
double currentGoalx, currentGoaly, currentGoalw;
int goalsSet = 0;
int goalsReached = 0;
int prevGoalStatus = 0;
int status = 0;

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

void updateMarkerLocation(double x, double y, double w) {
    // set the frame ID and timestamp
    marker.header.stamp = ros::Time::now();

    // set the location of the marker based on the current goal
    marker.pose.position.x = x;
    marker.pose.position.y = y;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.w = w;
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);
    // create a publisher to publish marker details to topic visualization_marker
    marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    
    // wait for the publisher to be ready
    ros::Duration(5).sleep();
    ros::spinOnce();
    while (marker_pub.getNumSubscribers() < 1) {
        if (!ros::ok()) {
            return 0;
        }
        ROS_WARN_ONCE("blocked while waiting for a subscriber to the marker");
    }
    ROS_INFO("marker_pub ready");

    // set the frame ID and timestamp
    marker.header.frame_id = "map";
    marker.ns = "add_markers";
    marker.id = 0;
    
    // get location details from rosparams
    double pickupX, pickupY, pickupW;
    nh.getParam("/location/pick_up_x", pickupX);
    nh.getParam("/location/pick_up_y", pickupY);
    nh.getParam("/location/pick_up_w", pickupW);
    double dropoffX, dropoffY, dropoffW;
    nh.getParam("/location/drop_off_x", dropoffX);
    nh.getParam("/location/drop_off_y", dropoffY);
    nh.getParam("/location/drop_off_w", dropoffW);

     
    // set the properties of the marker
    marker.scale.x = 0.3; 
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;

    // display pick up marker
    ROS_INFO("displaying pickup marker (%f, %f, %f)", pickupX, pickupY, pickupW);
    updateMarkerLocation(pickupX, pickupY, pickupW);
    marker.lifetime = ros::Duration(5);
    marker.header.stamp = ros::Time::now();
    marker_pub.publish(marker);
    ros::spinOnce();
    
    // display marker for 5s 
    ROS_INFO("waiting 5s");
    ros::Duration(3).sleep();

    // delete pickup marker
    ROS_INFO("deleting pickup marker");
    marker.action = visualization_msgs::Marker::DELETE; 
    marker_pub.publish(marker);

    // wait another 5s
    ROS_INFO("waiting 5s");
    ros::Duration(5).sleep();

    // display dropoff marker
    ROS_INFO("displaying dropoff marker (%f, %f, %f)", dropoffX, dropoffY, dropoffW);
    updateMarkerLocation(dropoffX, dropoffY, dropoffW);
    marker.type = visualization_msgs::Marker::CUBE;
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.lifetime = ros::Duration();
    marker.action = visualization_msgs::Marker::ADD; 
    marker_pub.publish(marker);

    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    } 
    return 0;    
}