#pragma once

#include "color.h"

namespace minirt {

class Vector3D;

class Material {
public:
    Material();
    Material(const Color &color);
    Material(const Color &color, double ambientCoeff, double diffuseCoeff, double specularCoeff, double shininess);

    Color shadeAmbient(const Color &lightAmbient) const;
    Color shadeDiffuseAndSpecular(const Color &light, const Vector3D &normal, const Vector3D &reflected, const Vector3D &toLight, const Vector3D &toViewer) const;

public:
    Color color;
    double ambientCoeff {0.5};
    double diffuseCoeff {0.5};
    double specularCoeff {0.5};
    double shininess {25};
};

}
