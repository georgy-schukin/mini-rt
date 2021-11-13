#include "scene_loader.h"

#include <stdexcept>

namespace minirt {

SceneLoader::SceneLoader() {}

void SceneLoader::loadSceneFromFile(const std::string &filename, Scene &scene) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    std::map<std::string, Material> materials;
    while (!in.eof()) {
        std::string tag;
        in >> tag;
        if (tag.empty()) {
            continue;
        }
        if (tag == "sphere") {
            const auto sphere = loadSphere(in);
            scene.addSphere(sphere);
        } else if (tag == "light") {
            const auto light = loadLight(in);
            scene.addLight(light);
        } else if (tag == "material") {
            std::string materialName;
            in >> materialName;
            materials[materialName] = loadMaterial(in);
        } else if (tag == "ambient") {
            Color color;
            in >> color;
            scene.setAmbient(color);
        } else if (tag == "background") {
            Color color;
            in >> color;
            scene.setBackground(color);
        } else if (tag == "recursion") {
            int limit;
            in >> limit;
            scene.setRecursionLimit(limit);
        } else {
            throw std::runtime_error("Unknown tag: " + tag);
        }
    }
}

Sphere SceneLoader::loadSphere(std::ifstream &in) {
    Point3D pos {0};
    double radius {1.0};
    Material material {Color {1.0}};
    Color color;
    while (!in.eof()) {
        std::string tag;
        in >> tag;
        if (tag.empty()) {
            continue;
        }
        if (tag == "pos") {
            in >> pos;
        } else if (tag == "radius") {
            in >> radius;
        } else if (tag == "material") {
            std::string materialName;
            in >> materialName;
            auto it = materials.find(materialName);
            if (it == materials.end()) {
                throw std::runtime_error("Unlnown material name: " + materialName);
            }
            material = it->second;
        } else if (tag == "color") {
            in >> color;
            material.setDiffuseAndSpecular(color);
        } else if (tag == "diffuse") {
            in >> color;
            material.setDiffuse(color);
        } else if (tag == "specular") {
            in >> color;
            material.setSpecular(color);
        } else if (tag == "shininess") {
            double shininess;
            in >> shininess;
            material.setShininess(shininess);
        } else if (tag == "transparent") {
            double refrCoeff, refrIndex;
            in >> refrCoeff >> refrIndex;
            material.makeTransparent(refrCoeff, refrIndex);
        } else if (tag == "end") {
            break;
        } else {
            throw std::runtime_error("Unknown sphere parameter: " + tag);
        }
    }
    return Sphere {pos, radius, material};
}

PointLight SceneLoader::loadLight(std::ifstream &in) {
    Point3D pos {0};
    Color color;
    while (!in.eof()) {
        std::string tag;
        in >> tag;
        if (tag.empty()) {
            continue;
        }
        if (tag == "pos") {
            in >> pos;
        } else if (tag == "color") {
            in >> color;
        } else if (tag == "end") {
            break;
        } else {
            throw std::runtime_error("Unknown light parameter: " + tag);
        }
    }
    return PointLight {pos, color};
}

Material SceneLoader::loadMaterial(std::ifstream &in) {
    Material material {Color {1.0}};
    Color color;
    while (!in.eof()) {
        std::string tag;
        in >> tag;
        if (tag.empty()) {
            continue;
        }
        if (tag == "color") {
            in >> color;
            material.setDiffuseAndSpecular(color);
        } else if (tag == "diffuse") {
            in >> color;
            material.setDiffuse(color);
        } else if (tag == "specular") {
            in >> color;
            material.setSpecular(color);
        } else if (tag == "shininess") {
            double shininess;
            in >> shininess;
            material.setShininess(shininess);
        } else if (tag == "transparent") {
            double refrCoeff, refrIndex;
            in >> refrCoeff >> refrIndex;
            material.makeTransparent(refrCoeff, refrIndex);
        } else if (tag == "end") {
            break;
        } else {
            throw std::runtime_error("Unknown material parameter: " + tag);
        }
    }
    return material;
}

}
