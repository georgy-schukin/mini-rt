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
    const auto aspect = static_cast<double>(resolutionX) / resolutionY;
    for (const auto &sample: samples) {
        const auto sx = static_cast<double>(x) + sample.x;
        const auto sy = static_cast<double>(y) + sample.y;
        // A ray from the eye.
        Vector3D rayDirection {
            sx * sizeX * aspect / resolutionX - sizeX * aspect / 2,
            sy * sizeY / resolutionY - sizeY / 2,
            distance};
        color += scene.illumination(Ray {viewPoint, rayDirection.normalized()});
    }
    return (color / numOfSamples).clamp();
}

}
