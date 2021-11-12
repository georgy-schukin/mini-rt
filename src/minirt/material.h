#pragma once

#include "color.h"

namespace minirt {

class Vector3D;

class Material {
public:
    Material();
    Material(const Color &color);
    Material(const Color &diffuse, const Color &specular, double shininess = 25);
    Material(const Color &color, double diffuseCoeff, double specularCoeff, double shininess = 25);

    void makeTransparent(double refrCoeff = 1.0, double refrIndex = 1.0);

    Color shade(const Color &lightColor, const Vector3D &normal, const Vector3D &reflected, const Vector3D &toLight, const Vector3D &toViewer) const;

public:
    Color diffuseColor {1, 1, 1};
    Color specularColor {1, 1, 1};
    double shininess {25};
    double refractionCoeff {0};
    double refractionIndex {1};
};

}
