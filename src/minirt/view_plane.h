#pragma once

#include "color.h"

namespace minirt {

class Point3D;
class Scene;

class ViewPlane {
public:
    ViewPlane();
    ViewPlane(int resolutionX, int resolutionY, double sizeX, double sizeY, double distance);

    // Compute color for the pixel with the given index.
    Color computePixel(const Scene &scene, const Point3D &viewPoint, int x, int y, int numOfSamples = 1);

private:
    int resolutionX;
    int resolutionY;
    double sizeX;
    double sizeY;
    double distance;
};

}
