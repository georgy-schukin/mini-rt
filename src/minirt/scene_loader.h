#pragma once

#include "scene.h"
#include "sphere.h"
#include "point_light.h"
#include "material.h"

#include <string>
#include <map>
#include <fstream>

namespace minirt {

class SceneLoader {
public:
    SceneLoader();

    void loadSceneFromFile(const std::string &filename, Scene &scene);

private:
    Sphere loadSphere(std::ifstream &in);
    PointLight loadLight(std::ifstream &in);
    Material loadMaterial(std::ifstream &in);

private:
    std::map<std::string, Material> materials;
};

}
