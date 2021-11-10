#include "view_plane.h"
#include "point_3d.h"
#include "scene.h"
#include "ray.h"

#include <algorithm>

namespace minirt {

ViewPlane::ViewPlane(int resolutionX, int resolutionZ, double sizeX, double sizeZ, double distance) :
    resolutionX(resolutionX), resolutionZ(resolutionZ),
    sizeX(sizeX), sizeZ(sizeZ), distance(distance) {            
}        

// Compute color for the pixel with the given index.
Color ViewPlane::computePixel(const Scene &scene, const Point3D &viewPoint, int x, int z, int numOfSamples) {
    Color color;
    for (int s = 0; s < numOfSamples; s++) {
        // Random sample in [-0.5, 0.5] from the pixel's center.
        double shiftX = (s > 0) ? double(rand() % 2000 - 1000) / 2000.0 : 0.0;
        double shiftZ = (s > 0) ? double(rand() % 2000 - 1000) / 2000.0 : 0.0;
        double sx = double(x) + shiftX;
        double sz = double(z) + shiftZ;
        // A ray from the eye.
        Vector3D rayDirection {
            sx * sizeX / resolutionX - sizeX / 2,
            distance,
            sz * sizeZ / resolutionZ - sizeZ / 2};            
        color += scene.illumination(Ray {viewPoint, rayDirection.normalized()});
    }
    color.red = std::min(color.red / numOfSamples, 1.0);
    color.green = std::min(color.green / numOfSamples, 1.0);
    color.blue = std::min(color.blue / numOfSamples, 1.0);
    return color;
}
	
}
