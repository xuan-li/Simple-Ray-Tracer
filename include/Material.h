#ifndef MATERIAL_H
#define MATERIAL_H
#include "Hitable.h"
#include "Ray.h"
#include <Eigen/Eigen>

class Material
{
  public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
  public:
    Lambertian(const Eigen::Vector3d &a);
    ~Lambertian() {}
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const;

  private:
    Eigen::Vector3d albedo;
};

class Metal : public Material
{
  public:
    Metal(Eigen::Vector3d &a, double f = 0);
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const;

  private:
    Eigen::Vector3d albedo;
    double fuzz;
};

class Dielectric : public Material
{
  public:
    Dielectric(double ri) : ref_idx(ri) {}
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) const;
  private:
    double ref_idx;
};

#endif // !MATERIAL_H
