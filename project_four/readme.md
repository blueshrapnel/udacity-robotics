# Udacity Project "Map My World"

Added `ros-noetic-rtabmap` and `ros-noetic-rtabmap_ros` to the docker image.

Open the following terminals, source each one first with `source devel/setup.bash`.
* Launch the world and the robot description:
`roslaunch simple_chassis_bot world.launch`
* Launch the tele-op controller, [teleop_twist_keyboard](https://github.com/ros-teleop/teleop_twist_keyboard):
`rosrun teleop_twist_keyboard teleop_twist_keyboard.py`
* Start the mapping node `roslaunch simple_chassis_bot mapping.launch`
* Start localisation node `roslaunch simple_chassis_bot localisation.launch` 

## Screenshots of mapping
* ![](db-view-3d-map.png)
* ![](db-view-car-wheels.png)

### Database File
* compressed and uploaded to DropBox, too large for github - uploading to DropBox
[`ground_floor_extras_car.zip`](https://www.dropbox.com/s/144v9e7z6dbutgi/ground_floor_extras_car.zip?dl=0)

## Screenshots of localisation
*  ![screenshot with car localised after moving around](localising.png)