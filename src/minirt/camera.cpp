#include "camera.h"

namespace minirt {

Camera::Camera() {}

Camera::Camera(const Point3D &viewPoint) {
    setViewPoint(viewPoint);
}

Camera::Camera(const Point3D &viewPoint, const Point3D &target, const Vector3D &up) {
    set(viewPoint, target, up);
}

void Camera::setViewPoint(const Point3D &point) {
    const auto shift = point - viewPoint;
    viewPoint = point;
    target = target + shift; // change target also
}

// Set camera's position and orientation: camera is located at viewPoint and looks at target.
void Camera::set(const Point3D &viewPoint, const Point3D &target, const Vector3D &up) {
    this->viewPoint = viewPoint;
    this->target = target;
    // Set up left-handed coordinate system for camera.
    unitZ = (target - viewPoint).normalized();
    unitX = up.cross(unitZ).normalized();
    unitY = unitZ.cross(unitX);
}

Ray Camera::rayFrom(double dx, double dy, double dz) const {
    Vector3D rayDirection = unitX * dx + unitY * dy + unitZ * dz;
    return Ray {viewPoint, rayDirection.normalized()};
}

void Camera::rotateAround(double radians, const Point3D &point) {

}

void Camera::rotateAroundTarget(double radians) {
    rotateAround(radians, target);
}

Camera Camera::rotatedAroundTarget(double radians) const {
    auto newCamera = *this;
    newCamera.rotateAroundTarget(radians);
    return newCamera;
}

const Point3D& Camera::getViewPoint() const {
    return viewPoint;
}

const Point3D& Camera::getTarget() const {
    return target;
}

const Vector3D& Camera::getUnitX() const {
    return unitX;
}

const Vector3D& Camera::getUnitY() const {
    return unitY;
}

const Vector3D& Camera::getUnitZ() const {
    return unitZ;
}

}
