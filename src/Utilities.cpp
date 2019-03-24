#include <Utilities.h>

Eigen::Vector3d random_in_unit_sphere()
{
    Eigen::Vector3d p;
    do
    {
        double x = double(rand()) / double(RAND_MAX + 1);
        double y = double(rand()) / double(RAND_MAX + 1);
        double z = double(rand()) / double(RAND_MAX + 1);
        p = 2.0 * Eigen::Vector3d(x, y, z).array() - 1;
    } while (p.norm() >= 1.0);
    return p;
}

Eigen::Vector3d reflect(const Eigen::Vector3d &v, const Eigen::Vector3d &n) { return v - 2 * v.dot(n) * n; }
