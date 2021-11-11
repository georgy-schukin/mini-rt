#include "minirt/minirt.h"

#include <cmath>

using namespace minirt;

void initScene(Scene &scene) {
    Color red = {1, 0.2, 0.2};
    Color blue = {0.2, 0.2, 1};
    Color green = {0.2, 1, 0.2};
    Color white = {0.8, 0.8, 0.8};
    Color yellow = {1, 1, 0.2};

    scene.addSphere(Sphere {{0, -2, 7}, 1, blue});
    scene.addSphere(Sphere {{-3, 2, 11}, 2, red});
    scene.addSphere(Sphere {{0, 2, 8}, 1, green});
    scene.addSphere(Sphere {{1.5, -0.5, 7}, 1, white});
    scene.addSphere(Sphere {{-2, -1, 6}, 0.7, yellow});
    scene.addSphere(Sphere {{2.2, 0.5, 9}, 1.2, white});
    scene.addSphere(Sphere {{4, -1, 10}, 0.7, red});

    scene.addLight(PointLight {{-15, 0, -15}, white});
    scene.addLight(PointLight {{1, 1, 0}, blue});
    scene.addLight(PointLight {{0, -10, 6}, red});
}

int main(int argc, char **argv) {
    int viewPlaneResolutionX = (argc > 1 ? std::stoi(argv[1]) : 600);
    int viewPlaneResolutionY = (argc > 2 ? std::stoi(argv[2]) : 600);
    int numOfSamples = (argc > 3 ? std::stoi(argv[3]) : 1);
    int numOfFrames = (argc > 4 ? std::stoi(argv[4]) : 1);

    Scene scene;
    scene.setBackground({0.05, 0.05, 0.05});
    scene.setAmbient({0.1, 0.1, 0.1});
    scene.setRecursionLimit(50);
    initScene(scene);

    const double backgroundSizeX = 4;
    const double backgroundSizeY = 4;
    const double backgroundDistance = 15;

    const double viewPlaneDistance = 5;
    const double viewPlaneSizeX = backgroundSizeX * viewPlaneDistance / backgroundDistance;
    const double viewPlaneSizeY = backgroundSizeY * viewPlaneDistance / backgroundDistance;

    ViewPlane viewPlane {viewPlaneResolutionX, viewPlaneResolutionY,
                         viewPlaneSizeX, viewPlaneSizeY, viewPlaneDistance};

    const double phi = 3.14159265358979323846;
    const double radius = 20;

    // Compute specified number of frames.
    for (int n = 0; n < numOfFrames; n++) {
        // Camera is rotating around (0, 0) origin.
        const double angle = phi * double(n) / 360.0 + 3.0 * phi / 2.0;
        Point3D viewPoint {radius * std::cos(angle), 0, radius * std::sin(angle)};

        Image image(viewPlaneResolutionX, viewPlaneResolutionY); // computed image
        for(int x = 0; x < viewPlaneResolutionX; x++)
        for(int y = 0; y < viewPlaneResolutionY; y++) {
            const auto color = viewPlane.computePixel(scene, viewPoint, x, y, numOfSamples);
            image.set(x, y, color);
        }

        image.saveJPEG("raytracing_" + std::to_string(n) + ".jpg");
    }

    return 0;
}
