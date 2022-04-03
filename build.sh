#!/bin/bash

# arguments:
# 1 (required): the godot executable file with path
# 2 (optional): the number of thread for the build

GODOT_EXECUTABLE="$1"

if [ -z "$2" ]; then
  BUILD_J=""
else
  BUILD_J="-j$2"
fi

scons target=debug "$BUILD_J"

#$GODOT_EXECUTABLE --debug --headless --path ./server
$GODOT_EXECUTABLE --path ./server
