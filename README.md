To build from source, you have to:
- Install GLFW
- Add glad.c to src folder.
- Add glad folder from include to usr/include.
- Add stb_image.h to src folder.
- Install CMake and g++.

To see line count run `cloc --exclude-list-file=.clocignore src`

for dockerization run `docker build -t 3d_demo:latest .` and `sudo docker run --security-opt seccomp=unconfined --security-opt label=disable --tmpfs /tmp:exec --mount type=tmpfs,target=/dev/shm --device /dev/dri   -e DISPLAY=$DISPLAY   -v /tmp/.X11-unix:/tmp/.X11-unix 3d_demo:latest
`
