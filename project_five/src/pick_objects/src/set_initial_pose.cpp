#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

// initialise ROS publisher
ros::Publisher pub;

int main(int argc, char **argv) {
    ros::init(argc, argv, "set_initial_pose");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10);

    // create initial pose message
    geometry_msgs::PoseWithCovarianceStamped initialPose;
    initialPose.header.frame_id = "map";
    initialPose.header.stamp = ros::Time::now();
    // setting pose to agree with launch file
    initialPose.pose.pose.position.x = -3.0;
    initialPose.pose.pose.position.y = 1.0;
    initialPose.pose.pose.position.z = 0;
    initialPose.pose.pose.orientation.x = 0.0;
    initialPose.pose.pose.orientation.y = 0.0;   
    initialPose.pose.pose.orientation.z = 0.0; 
    initialPose.pose.pose.orientation.w = 1.0;
    // for now ignoring covariance matrix

    while (pub.getNumSubscribers()<1){
        // wait for publisher and listener node to be ready
    }
    ROS_INFO("publishing initial pose");
    pub.publish(initialPose);
    ros::spinOnce();
    return 0;
}
