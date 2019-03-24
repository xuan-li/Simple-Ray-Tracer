#ifndef SPHERE_H
#define SPHERE_H
#include "Hitable.h"
#include "Ray.h"
#include <Eigen/Eigen>
#include "Material.h"

class Sphere : public Hitable
{
  public:
    Sphere() {}
    Sphere(Eigen::Vector3d &center, double R, std::shared_ptr<Material> mat);
    Eigen::Vector3d normal(Eigen::Vector3d point) const;
    Eigen::Vector3d center() const { return m_center; }
    double R() { return m_R; }
    ~Sphere() {}
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;

  private:
    double m_R;
    std::shared_ptr<Material> m_mat;
    Eigen::Vector3d m_center;
};

#endif
