#include <Utilities.h>

Eigen::Vector3d random_in_unit_sphere()
{
    Eigen::Vector3d p;
    do
    {
        double x = random01();
        double y = random01();
        double z = random01();
        p = 2.0 * Eigen::Vector3d(x, y, z).array() - 1;
    } while (p.norm() >= 1.0);
    return p;
}

Eigen::Vector3d reflect(const Eigen::Vector3d &v, const Eigen::Vector3d &n) { return v - 2 * v.dot(n) * n; }

bool refract(const Eigen::Vector3d &v, const Eigen::Vector3d &n, double ni_over_nt, Eigen::Vector3d &refracted)
{
    Eigen::Vector3d uv = v.normalized();
    double dt = uv.dot(n);
    double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
        return false;
}

double schlick(double cosine, double ref_idx)
{
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

double random01() { return double(rand()) / double(RAND_MAX + 1); }
