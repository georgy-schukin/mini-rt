#include "ray.h"

namespace minirt {

Ray::Ray() {}

Ray::Ray(const Point3D &origin, const Vector3D &direction) :
	origin(origin), direction(direction) {
}	

}
