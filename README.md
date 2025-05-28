# MiniRT 
A simple, CPU-based ray tracer built in C using the minilibx graphical library (42's X11 API)

## 🗣️ About

> _This raytracer is capable of rendering static scenes with varying numbers of light sources and shapes, including planes, spheres and cylinders_ 

For more detailed information, look at the [**subject of this project.**](https://github.com/edenjamsalem/miniRT/blob/master/subject.pdf)


## How to use

### For LINUX
Install dependencies:
```
$ sudo apt-get install -y libxext-dev && sudo apt-get install -y libxrandr-dev && sudo apt-get install -y libx11-dev && sudo apt-get install -y libbsd-dev && sudo apt-get install -y libssl-dev
```
Run:
```
make libs
make linux
./miniRT ./scenes/FILENAME X Y
```

### For MAC
```
make libs
make mac
./miniRT ./scenes/FILENAME X Y
```

Choose a ``FILENAME`` from the ./scenes folder, or make your own !

**Optional arguments:**
 _(defaults are used if none specified)_

``X`` = Number of rays per pixel

``Y`` = Number of shadow rays per pixel


## Capabilities

- Renders scenes with planes, spheres and cylinders of any colour

- Handles intersecting objects and cameras inside objects

- Implements optional surface properties to dull/sharpen reflectivity of objects

- Handles ambient light and multiple, coloured light sources

- Can specify the number of rays and shadow rays fired per pixel to determine overall image quality and rendering time


## Potential Improvements

Currently the mac version is compiling but not running on my Mac M1. I need to troubleshoot this !!

Given more time, I would really like to implement bitmaps to add textures to the objects