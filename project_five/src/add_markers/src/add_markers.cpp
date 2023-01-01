#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <actionlib_msgs/GoalStatusArray.h>

double poseAMCLx, poseAMCLy, poseAMCLw;
double currentGoalx, currentGoaly, currentGoalw;

void poseAMCLCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msgAMCL) {
    // extract relevant values, x, y, yaw
    poseAMCLx = msgAMCL->pose.pose.position.x;
    poseAMCLy = msgAMCL->pose.pose.position.y;
    poseAMCLw = msgAMCL->pose.pose.orientation.w;
    ROS_INFO("curent pose: %f, %f, %f", poseAMCLx, poseAMCLy, poseAMCLw);
}

void currentGoalCallback(const geometry_msgs::PoseStamped::ConstPtr& msgCurrentGoal) {
    // extract goal location for marker location
    currentGoalx = msgCurrentGoal->pose.position.x;
    currentGoaly = msgCurrentGoal->pose.position.y;
    currentGoalw = msgCurrentGoal->pose.orientation.w;
    ROS_INFO("current goal: %f, %f, %f", currentGoalx, currentGoaly, currentGoalw);
}

void goalStatusCallback(const actionlib_msgs::GoalStatusArray& msg ) {
    // extract status
    int status = msg->status_list.status;
    ROS_INFO("status: %d", status);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate loop_rate(1);
    // create a publisher to publish marker details to topic visualization_marker
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    // create a subscriber to the acml_pose topic
    ros::Subscriber pose_sub = n.subscribe("amcl_pose", 1000, poseAMCLCallback);

    // create a subscriber to the /move_base/current_goal topic
    ros::Subscriber current_goal_sub = n.subscribe("/move_base/current_goal", 10, currentGoalCallback);

    // create a subscrober to the /move_base/status topic
    ros::Subscriber goal_status = n.subscribe("/move_base/status", 10, goalStatusCallback);

    // create a single marker
    uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // set the frame ID and timestamp
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "single_marker";
    marker.id = 0;
    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;

    // set the location of the marker
    marker.pose.position.x = 1.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 1.0; 
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    // wait for the publisher to be ready
    while (marker_pub.getNumSubscribers() < 1) {
        if (!ros::ok()) {
            return 0;
        }
        ROS_WARN_ONCE("blocked while waiting for a subscriber to the marker");
    }
    ROS_INFO("marker_pub ready");
    marker_pub.publish(marker);

    ros::spin();
    return 0;    
}