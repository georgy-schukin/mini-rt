#pragma once

#include "color.h"
#include "vector_3d.h"
#include "point_3d.h"

namespace minirt {

class Point3D;
class Scene;

class ViewPlane {
public:
    ViewPlane();
    ViewPlane(int resolutionX, int resolutionY, double sizeX, double sizeY, double distance);

    // Compute color for the pixel with the given index.
    Color computePixel(const Scene &scene, int x, int y, int numOfSamples = 1);

    // Set camera's position only.
    void setViewPoint(const Point3D &eye);
    // Set camera's position and orientation: camera is located at eye and looks at lookAt.
    void setView(const Point3D &eye, const Point3D &lookAt, const Vector3D &up = {0, 1, 0});

private:
    int resolutionX;
    int resolutionY;
    double sizeX;
    double sizeY;
    double distance; // distance to view plane from view point

    // Camera's position.
    Point3D viewPoint {0, 0, 0};
    // Unit basis vectors for camera (left-handed system).
    Vector3D unitX {1, 0, 0};
    Vector3D unitY {0, 1, 0};
    Vector3D unitZ {0, 0, 1};
};

}
