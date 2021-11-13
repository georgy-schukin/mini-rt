# Mini-Rt
Very simple ray tracer

![raytracing result](doc/raytracing.jpg)

## Features

- Objects: spheres
- Lights: point lights
- Phong shading
- Reflection and refraction (transparency)
- Saving result in JPEG
- Loading scene from file

## Installation

### With CMake

```
git clone ...
mkdir mini-rt-build
cd mini-rt-build
cmake ../mini-rt/src
make 
make install
```

### With Qt

Just build included Qt project in `src`.

## [Documentation](doc/Manual.md)

## Examples

Directory `src/test` contains example program which renders a sample scene or scene from a file.

Examples of scene files are in `scenes` directory.

Enjoy!
