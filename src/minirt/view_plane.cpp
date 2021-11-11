#include "view_plane.h"
#include "point_3d.h"
#include "scene.h"
#include "ray.h"
#include "sampler.h"

#include <algorithm>

namespace minirt {

ViewPlane::ViewPlane(int resolutionX, int resolutionZ, double sizeX, double sizeZ, double distance) :
    resolutionX(resolutionX), resolutionZ(resolutionZ),
    sizeX(sizeX), sizeZ(sizeZ), distance(distance) {
}

// Compute color for the pixel with the given index.
Color ViewPlane::computePixel(const Scene &scene, const Point3D &viewPoint, int x, int z, int numOfSamples) {
    Color color;
    std::vector<Sample2D> samples;
    if (numOfSamples == 1) {
        // One sample - use pixel's center.
        samples = {{0.5, 0.5}};
    } else {
        // Use random samples.
        Sampler sampler;
        samples = sampler.sampleRandom(numOfSamples);
    }
    for (const auto &sample: samples) {
        double sx = double(x) + sample.x;
        double sz = double(z) + sample.y;
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
