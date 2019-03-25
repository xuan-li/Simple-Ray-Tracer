#ifndef UTILITIES
#define UTILITIES

#include <Eigen/Eigen>

Eigen::Vector3d random_in_unit_sphere();
Eigen::Vector3d reflect(const Eigen::Vector3d &v, const Eigen::Vector3d &n);
bool refract(const Eigen::Vector3d &v, const Eigen::Vector3d &n, double ni_over_nt, Eigen::Vector3d &refracted);
double schlick(double cosine, double ref_idx);

#endif // !UTILITIES
