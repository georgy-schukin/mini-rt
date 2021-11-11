#include "material.h"
#include "vector_3d.h"

#include <algorithm>
#include <cmath>

namespace minirt {

Material::Material() {}

Material::Material(const Color &color) :
    color(color) {
}

Material::Material(const Color &color, double ambientCoeff, double diffuseCoeff, double specularCoeff, double shininess) :
    color(color), ambientCoeff(ambientCoeff), diffuseCoeff(diffuseCoeff), specularCoeff(specularCoeff), shininess(shininess) {
}

Color Material::shadeAmbient(const Color &lightAmbient) const {
    return ambientCoeff * lightAmbient;
}

Color Material::shadeDiffuseAndSpecular(const Color &light, const Vector3D &normal, const Vector3D &reflected, const Vector3D &toLight, const Vector3D &toViewer) const {
    double diffuse = std::max(toLight.dot(normal), 0.0);
    double specular = 0.0;
    if (diffuse > 0.0) {
        specular = std::pow(std::max(reflected.dot(toViewer), 0.0), shininess);
    }
    return (diffuseCoeff * diffuse + specularCoeff * specular) * light;
}

}
