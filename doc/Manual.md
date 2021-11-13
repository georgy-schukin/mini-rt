# Starting using Mini-Rt

    #include "minirt/minirt.h"

# Creating materials

The same color for diffuse and specular:

    Material m1 {Color {1, 0, 0}};

Different colors for diffuse and specular, with a shininess value:

    Material m2 {Color {0.2, 0, 0}, Color {0.8, 0.5, 0.5}, 50};

Making material transparent by setting refraction amount (0 - min, 1 - max) and refraction index:

    Material m3 {Color {0.2}};
    m3.makeTransparent(0.9, 1.33);

# Creating objects

# Creating lights

# Setting up a scene

Scene object contains all information:

    Scene scene;

Add objects:

    scene.addObject(sphere);

Add lights:

    scene.addLight(light);

You can also set background color:

    scene.setBackground(Color {0.1, 0.1, 0.2});

And ambient light:

    scene.setAmbient(Color {0.1, 0.1, 0.1});

Setting maximum depth of recursion for computing reflection and refraction:

    scene.setRecursionLimit(10);

# Setting up a camera (view)

First you need to create a view plane:

    ViewPlane plane {resolutionX, resolutionY, sizeX, sizeY, distance};

Here resolutionX and resolutionY are resolution in pixels by X (width) and Y (height) respectively, for example, 1920x1080.
sizeX and sizeY are plane width and height in world coordinates, distance - distance from a camera in world coordinates.

By default a camera for the view plane is located in the origin (0, 0, 0) and oriented towards positive Z axis, 
with positive Y axis pointing up and positive X axis - to the right.

You can change default camera position:

    plane.setViewPoint(Point3D {10, 0, 10});

Or change camera position and orientation too:

    Point3D viewPoint {10, 2, 10};
    Point3D lookAt {0, 0, 0};
    plane.setView(viewPoint, lookAt);

Here the camera will be located at viewPoint and looking at lookAt. 
The third optional parameter for setView is 'up' direction (positive Y axis, i.e. (0, 1, 0), by default).

# Rendering a pixel

    Color color = plane.computePixel(scene, x, y, numberOfSamples);

This computes color for the pixel with an index (x, y), counting from the bottom left corner of the image.
numberOfSamples parameter specifies how many samples to do for the pixel. 
With default value 1 center of the pixel will be used to trace a ray, 
otherwise specified number of random positions within the pixel will be used.

# Rendering an image

To store a rendered image let's create it first:

    Image image {width, height};

Here is the main loop for rendering the image:

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            image.set(x, y, plane.computePixel(scene, x, y, numberOfSamples));

# Saving a result
You can save a result as JPEG file:

    image.saveJPEG("result.jpg", quality);

quality is a value from 1 to 100 which controls the saved image's quality. By default quallity = 90.