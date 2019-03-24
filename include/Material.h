#ifndef MATERIAL_H
#define MATERIAL_H
#include "Hitable.h"
#include "Ray.h"
#include <Eigen/Eigen>

class Material
{
  public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered) = 0;
};

class Lambertian : public Material
{
  public:
    Lambertian(const Eigen::Vector3d &a);
    ~Lambertian() {}
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered);

  private:
    Eigen::Vector3d albedo;
};

class Metal : public Material
{
  public:
    Metal(Eigen::Vector3d &a);
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Eigen::Vector3d &attenuation, Ray &scattered);
  private:
    Eigen::Vector3d albedo;
};

#endif // !MATERIAL_H
