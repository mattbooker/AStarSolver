# AStarSolver
Take home challenge for Weston Robotics

## Requirements
This solution has been tested with OpenCV 4.2.0 but should work with any 4.X version.

```
sudo apt update && sudo apt upgrade
sudo apt install libopencv-dev
```

## Building
```
git clone https://github.com/mattbooker/AStarSolver.git
cd AStarSolver
mkdir build
cd build
cmake ..
make .
```

## Usage
The -i flag allows you to specify which input image you would like to use.
The -s flag denotes which pixel in the image to use as the start location
The -g flag denotes which pixel in the image to use as the goal location
```
./AStarSolver -i <path to input map> -s x,y -g x,y
```
