#include <Camera.h>
#include <Scene.h>
#include <iostream>

int main(int argc, char **argv)
{
    Scene scene;
    // add a ball at the center of the screen;
    auto mat1 = std::make_shared<Lambertian>(Lambertian(Eigen::Vector3d(0.8, 0.3, 0.3)));
    auto sphere1 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, 0, -1), 0.5, mat1));
    scene.add_object(sphere1);

    auto mat2 = std::make_shared<Metal>(Metal(Eigen::Vector3d(0.8, 0.6, 0.2)));
    auto sphere2 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(1, 0, -1), 0.5, mat2));
    scene.add_object(sphere2);

    auto mat3 = std::make_shared<Metal>(Metal(Eigen::Vector3d(0.8, 0.8, 0.8)));
    auto sphere3 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(-1, 0, -1), 0.5, mat3));
    scene.add_object(sphere3);

    // use a ball as the floor;
    auto mat4 = std::make_shared<Lambertian>(Lambertian(Eigen::Vector3d(0.8, 0.8, 0.0)));
    auto sphere4 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, -100.5, -1), 100, mat4));
    scene.add_object(sphere4);

    Camera camera;
    camera.take_photo("screen.ppm", scene);
    return 0;
}