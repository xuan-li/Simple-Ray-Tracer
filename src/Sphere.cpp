#include <Sphere.h>

Sphere::Sphere(Eigen::Vector3d &center, double R):m_R(R), m_center(center) {}

Eigen::Vector3d Sphere::normal(Eigen::Vector3d point)
{
    return (point - m_center).normalized();
}


bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    Eigen::Vector3d oc = r.origin() - m_center;
    double a = r.direction().dot();
    
}
