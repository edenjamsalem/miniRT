# Minishell 🐚
A lightweight implementation of a Bash-like shell

## 🗣️ About

> _This project is a simple, CPU-based ray tracer built on the minilibx graphical library (42's X11 API)_ 

For more detailed information, look at the [**subject of this project.**](https://github.com/edenjamsalem/miniRT/blob/master/subject.pdf)


## How to use it

```
make libs
make linux (or make mac)
./miniRT ./scenes/FILENAME X Y
```

Choose a ``FILENAME`` from the ./scenes folder, or make your own !

**Optional arguments:**
``X`` = Number of rays per pixel
``Y`` = Number of shadow rays per pixel
_(defaults are used if none specified)_


## Available options

- Capable of rendering scenes with planes, spheres and cylinders of any colour

- Handles logic for intersecting objects and camera inside objects

- Implements surface properties to dull/sharpen reflectivity of objects

- Can handle ambient light and multiple light sources of any specific colour

- Option to specify the number of rays and shadow rays fired per pixel to determine overall image quality and rendering time


## Potential Improvements

Currently the mac version is compiling but is not running on my Mac M1. I need to troubleshoot this.