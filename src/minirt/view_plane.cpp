#include "view_plane.h"
#include "point_3d.h"
#include "scene.h"
#include "ray.h"
#include "sampler.h"

#include <algorithm>

namespace minirt {

ViewPlane::ViewPlane(int resolutionX, int resolutionY, double sizeX, double sizeY, double distance) :
    resolutionX(resolutionX), resolutionY(resolutionY),
    sizeX(sizeX), sizeY(sizeY), distance(distance) {
}

// Compute color for the pixel with the given index.
Color ViewPlane::computePixel(const Scene &scene, const Point3D &viewPoint, int x, int y, int numOfSamples) {
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
        double sy = double(y) + sample.y;
        // A ray from the eye.
        Vector3D rayDirection {
            sx * sizeX / resolutionX - sizeX / 2,
            sy * sizeY / resolutionY - sizeY / 2,
            distance};
        color += scene.illumination(Ray {viewPoint, rayDirection.normalized()});
    }
    color.red = std::min(color.red / numOfSamples, 1.0);
    color.green = std::min(color.green / numOfSamples, 1.0);
    color.blue = std::min(color.blue / numOfSamples, 1.0);
    return color;
}

}
