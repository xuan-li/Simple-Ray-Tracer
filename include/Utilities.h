#ifndef UTILITIES
#define UTILITIES

#include <Eigen/Eigen>

Eigen::Vector3d random_in_unit_sphere();
Eigen::Vector3d reflect(const Eigen::Vector3d &v, const Eigen::Vector3d &n);

#endif // !UTILITIES
