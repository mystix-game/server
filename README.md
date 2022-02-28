# server
This is a Godot 4 alpha authoritative server written in c++

## Get started

Download and build Godot 4 master branch:
```bash
#Install build dependencies
sudo apt-get install build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev yasm

#Download godot 4 from master branch
git clone https://github.com/godotengine/godot.git
cd godot

#Compile godot editor
scons -j16 platform=linuxbsd

#Compile godot export tools
scons -j16 platform=x11 tools=no target=release_debug bits=64
```

Download and build server:
```bash
#Download
git clone https://github.com/mystix-game/server.git
cd server
git submodule update --init --recursive

#Build
cd godot-cpp/
scons platform=linux target=debug generate_bindings=yes -j16
cd ..
scons target=debug -j16
```


