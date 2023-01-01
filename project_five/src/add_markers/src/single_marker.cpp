#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "single_marker");
    ros::NodeHandle n;
    ros::Rate loop_rate(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    uint32_t shape = visualization_msgs::Marker::CUBE;

    while (ros::ok()) {
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
        while (marker_pub.getNumSubscribers() < 1)
        {
        if (!ros::ok())
        {
            return 0;
        }
        ROS_WARN_ONCE("blocked while waiting for a subscriber to the marker");
        sleep(1);
        }
        ROS_INFO("marker_pub ready");
        marker_pub.publish(marker);


        // Cycle between different shapes
        switch (shape)
        {
            case visualization_msgs::Marker::CUBE:
                shape = visualization_msgs::Marker::SPHERE;
                break;
            case visualization_msgs::Marker::SPHERE:
                shape = visualization_msgs::Marker::ARROW;
                break;
            case visualization_msgs::Marker::ARROW:
                shape = visualization_msgs::Marker::CYLINDER;
                break;
            case visualization_msgs::Marker::CYLINDER:
                shape = visualization_msgs::Marker::CUBE;
                break;
        }

        loop_rate.sleep();

    }
    return 0;    
}