# server
This is a Godot 4 alpha authoritative server written in c++

## start

download:
```bash
git clone https://github.com/mystix-game/server.git
git submodule update --init --recursive
```

build:
```bash
cd godot-cpp/
scons platform=linux target=debug generate_bindings=yes -j16
cd ..
scons target=debug -j16
```
