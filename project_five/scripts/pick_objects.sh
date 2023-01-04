#!/bin/bash

# https://ryan.himmelwright.net/post/scripting-tmux-workspaces/
# https://how-to.dev/how-to-create-tmux-session-with-a-script

# set session name - test localisation and navigation using simpler single room world
SESSION="test-local-nav"
tmux new-session -d -s $SESSION

# main window is a shell called main
window=0
tmux rename-window -t $SESSION:$window 'main'

# launch gazebo window with turtlbot 3
# docker container sets environment variable `TURLEBOT3_MODEL=burger`
window=1
tmux new-window -t $SESSION:$window -n 'gazebo'
tmux send-keys -t $SESSION:$window 'source $HOME/project_five/devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'roslaunch home_service_world turtlebot3_single_room.launch' C-m
sleep 5

# launch navigation stack
window=2
tmux new-window -t $SESSION:$window -n 'navigation'
tmux send-keys -t $SESSION:$window 'source $HOME/project_five/devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'roslaunch home_service_world turtlebot3_navigation.launch' C-m
sleep 5

# run pick_object
window=3
tmux new-window -t $SESSION:$window -n 'pick_objects'
tmux send-keys -t $SESSION:$window 'source $HOME/project_five/devel/setup.bash' C-m
tmux send-keys -t $SESSION:$window 'rosrun pick_objects set_initial_pose' C-m
tmux send-keys -t $SESSION:$window 'roslaunch pick_objects pick_objects.launch' C-m

# attach session on the main window
tmux attach-session -t $SESSION