#include "scene.h"
#include "ray.h"

#include <limits>
#include <algorithm>
#include <stdexcept>
#include <fstream>

namespace minirt {

Scene::Scene() {}

void Scene::addSphere(const Sphere &sphere) {
    spheres.push_back(sphere);
}

void Scene::addLight(const PointLight &light) {
    lights.push_back(light);
}

void Scene::setAmbient(const Color &color) {
    ambientLight = color;
}

void Scene::setBackground(const Color &color){
    backgroundColor = color;
}

void Scene::setRecursionLimit(int limit) {
    limitOfRecursion = limit;
}

void Scene::loadFromFile(const std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    Point3D pos;
    Color color;
    while (!in.eof()) {
        std::string tag;
        in >> tag;
        if (tag == "sphere") {
            double radius;
            in >> pos.x >> pos.y >> pos.z
                >> radius
                >> color.red >> color.green >> color.blue;
            addSphere(Sphere {pos, radius, color});
        } else if (tag == "light") {
            in >> pos.x >> pos.y >> pos.z
                >> color.red >> color.green >> color.blue;
            addLight(PointLight {pos, color});
        } else if (tag == "ambient") {
            in >> color.red >> color.green >> color.blue;
            setAmbient(color);
        } else if (tag == "background") {
            in >> color.red >> color.green >> color.blue;
            setBackground(color);
        } else if (tag == "recursion") {
            int limit;
            in >> limit;
            setRecursionLimit(limit);
        } else {
            throw std::runtime_error("Unknown tag: " + tag);
        }
    }
}

// Returns closest object if there is an intersection or nullptr otherwise.
const Sphere* Scene::intersect(const Ray &ray, Point3D &closestIntersectionPoint) const {
    const Sphere *closestSphere = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    for (const auto &sphere: spheres) {
        double distance = 0;
        if (sphere.intersect(ray, distance) && distance < minDistance) {
            closestSphere = &sphere;
            minDistance = distance;
        }
    }
    if (closestSphere) {
        closestIntersectionPoint = ray.origin + ray.direction * minDistance;
    }
    return closestSphere;
}

// Compute color for this ray in the scene.
Color Scene::illumination(const Ray &ray, int recursionStep) const {
    if (recursionStep >= limitOfRecursion) {
        return Color();
    }
    // Find an object for intersection.
    Point3D closestIntersectionPoint;
    auto closestSphere = intersect(ray, closestIntersectionPoint);
    if (!closestSphere) {
        return backgroundColor;
    }

    // Normal for the sphere and reflected ray.
    Vector3D normal = (closestIntersectionPoint - closestSphere->position).normalized();
    Vector3D reflectedRayDirection = ray.direction - 2 * normal.dot(ray.direction) * normal;

    Color color;
    // Add illumination from each light.
    for (const auto &light: lights) {
        // Check if the point on the object is illuminated by this light (not obscured by an obstacle).
        Vector3D directionToLight = light.position - closestIntersectionPoint;
        double distanceToLight = directionToLight.length();
        directionToLight = directionToLight.normalized();
        Point3D intersectionPoint;
        auto obstacle = intersect(Ray {closestIntersectionPoint, directionToLight}, intersectionPoint);
        if (obstacle) {
            // Check if the light is closer then the intersected object.
            double distanceToObstacle = (intersectionPoint - closestIntersectionPoint).length();
            if (distanceToObstacle > distanceToLight) {
                obstacle = nullptr;
            }
        }
        if (!obstacle) {
            // Apply coefficients of the body color to the intensity of the light source.
            color += light.color * closestSphere->color * std::max(0.0, reflectedRayDirection.dot(directionToLight));
        }
    }

    // Add ambient light.
    color += ambientLight * closestSphere->color;

    // Add reflection.
    Ray reflectedRay {closestIntersectionPoint, reflectedRayDirection.normalized()};
    Color reflectionColor = illumination(reflectedRay, recursionStep + 1);
    color += closestSphere->color * reflectionColor;

    return color;
}

}
