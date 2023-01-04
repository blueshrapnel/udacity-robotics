#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
    ros::init(argc, argv, "multiple_navigation_goals");
    ros::NodeHandle nh;

    // tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    // get location details from rosparams
    double pickupX, pickupY, pickupW;
    nh.getParam("/location/pick_up_x", pickupX);
    nh.getParam("/location/pick_up_y", pickupY);
    nh.getParam("/location/pick_up_w", pickupW);
    double dropoffX, dropoffY, dropoffW;
    nh.getParam("/location/drop_off_x", dropoffX);
    nh.getParam("/location/drop_off_y", dropoffY);
    nh.getParam("/location/drop_off_w", dropoffW);

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    
    // pickup goal
    goal.target_pose.pose.position.x = pickupX;
    goal.target_pose.pose.position.y = pickupY;
    goal.target_pose.pose.position.z = 0;
    goal.target_pose.pose.orientation.w = pickupW;

    ROS_INFO("sending robot to pickup location");
    ac.sendGoal(goal);
    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        ROS_INFO("The robot has reached the first goal");

        // pause 5 seconds
        ros::Duration(5.0).sleep();
        ROS_INFO("The robot has picked up the object");
        // drop off location
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = dropoffX;
        goal.target_pose.pose.position.y = dropoffY;
        goal.target_pose.pose.position.z = 0.0;
        goal.target_pose.pose.orientation.w = dropoffW;

        ROS_INFO("sending robot to drop off location");
        ac.sendGoal(goal);
        ac.waitForResult();
        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Drop off location reached");
        }
    } else    
        ROS_INFO("The robot failed to move.");

    return 0;
}