#pragma once

#include "point_3d.h"
#include "vector_3d.h"
#include "color.h"

namespace minirt {

class Ray;

class Sphere {
public:
    Sphere(const Point3D &position, double radius = 1.0, const Color &color = Color(1));

    // Check intersection with the sphere.
    bool intersect(const Ray &ray, double &distance) const;

    Vector3D normalTo(const Point3D &surfacePoint) const;

public:
    Point3D position;
    double radius;
    Color color;
};

}
