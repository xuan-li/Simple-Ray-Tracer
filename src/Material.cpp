#include "Utilities.h"
#include <Material.h>

Lambertian::Lambertian(const Eigen::Vector3d &a) : albedo(a) {}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered)
{
    using namespace Eigen;
    Vector3d target = rec.p + rec.normal + random_in_unit_sphere();
    Vector3d d = target - rec.p;
    scattered = Ray(rec.p, d);
    attenuation = albedo;
    return true;
}

Metal::Metal(Eigen::Vector3d &a) : albedo(a) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered)
{
    using namespace Eigen;
    Vector3d reflected = reflect(r_in.direction().normalized(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return scattered.direction().dot(rec.normal) > 0;
}
