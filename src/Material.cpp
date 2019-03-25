#include "Utilities.h"
#include <Material.h>

Lambertian::Lambertian(const Eigen::Vector3d &a) : albedo(a) {}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const
{
    using namespace Eigen;
    Vector3d target = rec.p + rec.normal + random_in_unit_sphere();
    Vector3d d = target - rec.p;
    scattered = Ray(rec.p, d);
    attenuation = albedo;
    return true;
}

Metal::Metal(Eigen::Vector3d &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const
{
    using namespace Eigen;
    Vector3d reflected = reflect(r_in.direction().normalized(), rec.normal) + fuzz * random_in_unit_sphere();
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return scattered.direction().dot(rec.normal) > 0;
}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const
{
    Eigen::Vector3d outward_normal;
    Eigen::Vector3d reflected = reflect(r_in.direction(), rec.normal);
    double ni_over_nt;
    attenuation = Eigen::Vector3d::Ones();
    Eigen::Vector3d refracted;

    double reflect_prob;
    double cosine;

    if (r_in.direction().dot(rec.normal) > 0)
    {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * r_in.direction().dot(rec.normal) / r_in.direction().norm();
    }
    else
    {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -r_in.direction().dot(rec.normal) / r_in.direction().norm();
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else
    {
        reflect_prob = 1.0;
    }

    if (random01() < reflect_prob)
    {
        scattered = Ray(rec.p, reflected);
    }
    else
    {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}
