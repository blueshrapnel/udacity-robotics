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
ros::Subscriber current_goal_sub; 
ros::Subscriber goal_status;
 
visualization_msgs::Marker marker;

/*
void poseAMCLCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msgAMCL) {
    // extract relevant values, x, y, yaw
    poseAMCLx = msgAMCL->pose.pose.position.x;
    poseAMCLy = msgAMCL->pose.pose.position.y;
    poseAMCLw = msgAMCL->pose.pose.orientation.w;
    ROS_INFO("curent pose: %f, %f, %f", poseAMCLx, poseAMCLy, poseAMCLw);
}*/

void updateDropOffMarker() {
    // set the frame ID and timestamp
    marker.header.stamp = ros::Time::now();

    // set the location of the marker based on the current goal
    marker.pose.position.x = currentGoalx;
    marker.pose.position.y = currentGoaly;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.w = currentGoalw;
    marker.scale.x = 0.3; 
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    // moving to the drop off location
    marker.type = visualization_msgs::Marker::CUBE;
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    
}

void currentGoalCallback(const geometry_msgs::PoseStamped::ConstPtr& msgCurrentGoal) {
    // extract goal location for marker location
    currentGoalx = msgCurrentGoal->pose.position.x;
    currentGoaly = msgCurrentGoal->pose.position.y;
    currentGoalw = msgCurrentGoal->pose.orientation.w;
    goalsSet += 1;
    updateDropOffMarker();
    
    ROS_INFO("current goal: %f, %f, %f goals set %d, reached %d", currentGoalx, currentGoaly, currentGoalw, goalsSet, goalsReached);
}

void goalStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr& msg ) {
    actionlib_msgs::GoalStatusArray status_array = *msg;   
    uint32_t sequence = status_array.header.seq;

    // extract status
    if (!msg->status_list.empty()) {
        actionlib_msgs::GoalStatus goalStatus = msg->status_list[0];
        status = goalStatus.status;
        if (prevGoalStatus == 1 && status == 3) {
            goalsReached += 1;
            if (goalsReached == 1) {
                // reached pickup location, delete marker
                ROS_INFO("arrived at pickup, deleting pickup marker");
                marker.action = visualization_msgs::Marker::DELETE; 
                marker_pub.publish(marker);
            }
            if (goalsSet == 2) {
                // reached destination display drop-off marker
                ROS_INFO("arrived at drop off, showing location marker");
                marker.action = visualization_msgs::Marker::ADD;
                marker_pub.publish(marker);
            }
        }
        prevGoalStatus = status;
        //ROS_INFO("status: %d goal number %d, goals reached: %d", status, goalsSet, goalsReached);
    }
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    // create a publisher to publish marker details to topic visualization_marker
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    
    // wait for the publisher to be ready
    while (marker_pub.getNumSubscribers() < 1) {
        if (!ros::ok()) {
            return 0;
        }
        ROS_WARN_ONCE("blocked while waiting for a subscriber to the marker");
    }
    ROS_INFO("marker_pub ready");


    // publish the marker at the pick-up location before the robot starts moving
    // set the frame ID and timestamp
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "add_markers";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;

    // set the location of the marker
    marker.pose.position.x = 1.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.3; 
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();
    
    // publish marker
    marker_pub.publish(marker);

    // set up the subscribers - the call backs control the marker logic
    // ros::Subscriber pose_sub = n.subscribe("amcl_pose", 1000, poseAMCLCallback);
    current_goal_sub = n.subscribe("/move_base/current_goal", 10, currentGoalCallback);
    goal_status = n.subscribe("/move_base/status", 10, goalStatusCallback);

    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;    
}