#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <algorithm>
#include <vector>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Sending new motor command.");

    // motor command from arguments
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the DriveToTarget service and pass the requested motor command
    if (!client.call(srv))
        ROS_ERROR("Failed to call service /ball_chaser/command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    // /camera/rgb/image_raw message definition
    // http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/Image.html
    // top left corner (0,0)

    int height = img.height; // number of rows
    int width = img.width;   // number of cols
    int step = img.step;     // full row length in bytes

    // white pixel counters for each image region
    int left_counter = 0;
    int middle_counter = 0;
    int right_counter = 0;

    // region boundaries
    double middle_left_boundary = width / 3.0;
    double middle_right_boundar = width * 2.0 / 3.0; 

    // new motor commands
    float linear_x = 0.4;
    float angular_z = 0.0;

    // loop through all the pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // look for white pixel (255, 255, 255)
            int index = i * step + j * 3;
            int r = img.data[index]; // red
            int g = img.data[index + 1]; // green
            int b = img.data[index + 2]; // blue
            if (r==255 && g==255 && b==255) {
                // we have a white pixel
                // increase counter depending on region (left, middle or right)
                // cols: | 0 .. left ..  1/3 * width | .. middle .. 2/3 * width | .. right .. |
                if (j <= middle_left_boundary) {
                    ++left_counter;
                }
                else if (j <= middle_right_boundar) {
                    ++middle_counter;
                } else {
                    ++right_counter;
                }
            }
        }
    }

    // check for no white pixels 
    if (left_counter + right_counter + middle_counter < 1) {
        // no white pixels found, send zero values, default angular_z is 0
        linear_x = 0.0;
        ROS_INFO("STOP    : (%f, %f) : | left: %d | middle: %d | right: %d |", linear_x, angular_z, left_counter, middle_counter, right_counter);
    }
    else {
        std::vector<int> counts{left_counter, middle_counter, right_counter};
        // http://www.cplusplus.com/reference/algorithm/max_element/
        // https://en.cppreference.com/w/cpp/algorithm/max_element see last example
        int max_region_index = std::max_element(counts.begin(), counts.end()) - counts.begin();
        // adjust motor command according to the regions
        if (max_region_index == 1) {
            // middle region, go straight, use default values
            ROS_INFO("STRAIGHT: (%f, %f) : | left: %d | middle: %d | right: %d |", linear_x, angular_z, left_counter, middle_counter, right_counter);
        } else if(max_region_index == 2) {
            // right region, turn right, adjust angular_z
            angular_z = -0.5;
            ROS_INFO("RIGHT   : (%f, %f) : | left: %d | middle: %d | right: %d |", linear_x, angular_z, left_counter, middle_counter, right_counter);
        } else {
            // left region, turn left, adjust angular_z
            angular_z = 0.5;
            ROS_INFO("LEFT   : (%f, %f) : | left: %d | middle: %d | right: %d |", linear_x, angular_z, left_counter, middle_counter, right_counter);
        }
    }
    // send motor command
    drive_robot(linear_x, angular_z);
}

int main(int argc, char **argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}