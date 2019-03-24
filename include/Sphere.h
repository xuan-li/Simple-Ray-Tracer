#ifndef SPHERE_H
#define SPHERE_H
#include <Eigen/Eigen>
#include "Hitable.h"
#include "Ray.h"

class Sphere: public Hitable
{
public:
    Sphere() {}
    Sphere(Eigen::Vector3d &center, double R);
    Eigen::Vector3d normal(Eigen::Vector3d point);
    Eigen::Vector3d center() {return m_center;}
    double R() {return m_R;}
    ~Sphere() {}
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
private:
    double m_R;
    Eigen::Vector3d m_center;
};

#endif
