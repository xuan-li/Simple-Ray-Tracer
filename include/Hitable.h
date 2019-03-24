#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"
struct HitRecord
{
    double t;
    Eigen::Vector3d p;
    Eigen::Vector3d normal;
}

class Hitable
{
public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
}

#endif
