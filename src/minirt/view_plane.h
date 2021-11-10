#pragma once

#include "color.h"

namespace minirt {

class Point3D;
class Scene;	

class ViewPlane {
public:    
	ViewPlane();
    ViewPlane(int resolutionX, int resolutionZ, double sizeX, double sizeZ, double distance);

    // Compute color for the pixel with the given index.
    Color computePixel(const Scene &scene, const Point3D &viewPoint, int x, int z, int numOfSamples = 1);

private:    
    int resolutionX;
    int resolutionZ;
    double sizeX;
    double sizeZ;
    double distance;
};

}
