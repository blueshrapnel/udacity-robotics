#!/bin/bash

# https://ryan.himmelwright.net/post/scripting-tmux-workspaces/
# https://how-to.dev/how-to-create-tmux-session-with-a-script

# set session name
SESSION="test-slam"
tmux new-session -d -s $SESSION

# main window is a shell
window=0
tmux rename-window -t $SESSION:$window 'main'

# launch gazebo window
window=1
tmux new-window -t $SESSION:$window -n 'gazebo'
tmux send-keys -t $SESSION:$window 'source devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'roslaunch home_service_world turtlebot3_ground_floor.launch' C-m
sleep 5

# launch gmapping window (and visualisation)
window=2
tmux new-window -t $SESSION:$window -n 'gmapping'
tmux send-keys -t $SESSION:$window 'source devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'roslaunch turtlebot3_slam gmapping.launch slam_methods:=gmapping' C-m

# launch teleop window
window=3
tmux new-window -t $SESSION:$window -n 'teleop'
tmux send-keys -t $SESSION:$window 'source devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch' C-m

# attach session on the main window
tmux attach-session -t $SESSION