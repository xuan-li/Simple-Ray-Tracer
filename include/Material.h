#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
  public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, Eigen::Vector3d &attenuation, Ray &scattered) = 0;
};

#endif // !MATERIAL_H
