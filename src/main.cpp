#include <iostream>
#include <Scene.h>
#include <Camera.h>

int main(int argc, char **argv)
{
    Scene scene;
    // add a ball at the center of the screen;
    scene.add_object(std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, 0, -1), 0.5)));
    // use a ball as the floor;
    scene.add_object(std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, -100.5, -1), 100)));

	Camera camera;
    camera.take_photo("screen.ppm", scene);
    return 0;
}