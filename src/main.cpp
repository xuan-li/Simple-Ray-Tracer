#include <Camera.h>
#include <Scene.h>
#include <Utilities.h>
#include <iostream>

void random_scene(Scene &scene)
{
    using namespace Eigen;
    scene.add_object(std::make_shared<Sphere>(Vector3d(0, -1000, 0), 1000, std::make_shared<Lambertian>(Lambertian(Vector3d(0.5, 0.5, 0.5)))));
    int i = 1;
    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            float choose_mat = random01();
            Vector3d center(a + 0.9 * random01(), 0.2, b + 0.9 * random01());
            if ((center - Vector3d(4, 0.2, 0)).norm() > 0.9)
            {
                if (choose_mat < 0.8)
                { // diffuse
                    auto mat = std::make_shared<Lambertian>(Lambertian(Vector3d(random01() * random01(), random01() * random01(), random01() * random01())));
                    auto sphere = std::make_shared<Sphere>(Sphere(center, 0.2, mat));
                    scene.add_object(sphere);
                }
                else if (choose_mat < 0.95)
                { // metal
                    auto mat =
                        std::make_shared<Metal>(Metal(Vector3d(0.5 * (1 + random01()), 0.5 * (1 + random01()), 0.5 * (1 + random01())), 0.5 * random01()));
                    auto sphere = std::make_shared<Sphere>(Sphere(center, 0.2, mat));
                    scene.add_object(sphere);
                }
                else
                { // glass
                    auto mat = std::make_shared<Dielectric>(Dielectric(1.5));
                    auto sphere = std::make_shared<Sphere>(Sphere(center, 0.2, mat));
                    scene.add_object(sphere);
                }
            }
        }
    }

    auto mat1 = std::make_shared<Dielectric>(Dielectric(1.5));
    auto sphere = std::make_shared<Sphere>(Sphere(Vector3d(0, 1, 0), 1.0, mat1));
    scene.add_object(sphere);

    auto mat2 = std::make_shared<Lambertian>(Lambertian(Vector3d(0.4, 0.2, 0.1)));
    sphere = std::make_shared<Sphere>(Sphere(Vector3d(-4, 1, 0), 1.0, mat2));
    scene.add_object(sphere);

    auto mat3 = std::make_shared<Metal>(Metal(Vector3d(0.7, 0.6, 0.5), 0.1));
    sphere = std::make_shared<Sphere>(Sphere(Vector3d(4, 1, 0), 1.0, mat3));
    scene.add_object(sphere);
}

int main(int argc, char **argv)
{
    Scene scene;

    random_scene(scene);
    // add a ball at the center of the screen;
    // auto mat1 = std::make_shared<Lambertian>(Lambertian(Eigen::Vector3d(0.8, 0.3, 0.3)));
    // auto sphere1 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, 0, -1), 0.5, mat1));
    // scene.add_object(sphere1);

    // auto mat2 = std::make_shared<Metal>(Metal(Eigen::Vector3d(0.8, 0.6, 0.2), 0.3));
    // auto sphere2 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(1, 0, -1), 0.5, mat2));
    // scene.add_object(sphere2);

    // auto mat3 = std::make_shared<Dielectric>(Dielectric(1.5));
    // auto sphere3 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(-1, 0, -1), 0.5, mat3));
    // scene.add_object(sphere3);

    // auto sphere5 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(-1, 0, -1), -0.45, mat3));
    // scene.add_object(sphere5);

    //// use a ball as the floor;
    // auto mat4 = std::make_shared<Lambertian>(Lambertian(Eigen::Vector3d(0.8, 0.8, 0.0)));
    // auto sphere4 = std::make_shared<Sphere>(Sphere(Eigen::Vector3d(0, -100.5, -1), 100, mat4));
    // scene.add_object(sphere4);

    Eigen::Vector3d look_from(13, 2, 3);
    Eigen::Vector3d look_at(0, 0, 0);
    Camera camera(look_from, look_at, Eigen::Vector3d(0, 1, 0), 20, 1200. / 800., 0.1, 10.0);
    camera.take_photo("screen.ppm", scene, 1200, 800, 10);
    return 0;
}