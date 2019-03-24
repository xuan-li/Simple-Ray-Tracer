#include "Camera.h"
#include <memory>

Camera::Camera() : ns(100), w(200), h(100), m_lower_left_corner(-2.0, -1.0, -1.0), m_horizontal(4.0, 0.0, 0.0), m_vertical(0.0, 2.0, 0.0), m_origin(0, 0, 0) {}

Camera::~Camera() {}

void Camera::take_photo(std::string filename, const Scene &world)
{
    Image image(w, h);
    for (int j = h - 1; j >= 0; --j)
    {
        for (int i = 0; i < w; ++i)
        {

            std::vector<Eigen::Vector3d> cols(ns);
            std::vector<double> us(ns);
            std::vector<double> vs(ns);
            for (int s = 0; s < ns; ++s)
            {
                us[s] = double(i + rand() / double(RAND_MAX + 1)) / double(w);
                vs[s] = double(j + rand() / double(RAND_MAX + 1)) / double(h);
            }
#pragma omp parallel
            {
#pragma omp for
                for (int s = 0; s < ns; ++s)
                {
                    // (u, v) is the screen coordinate of the intersection of the ray and the screen.
                    Ray r = get_ray(us[s], vs[s]);
                    cols[s] = color(r, world);
                }
            }

            Eigen::Vector3d col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                col += cols[s];
            }
            col /= ns;
            col = col.cwiseSqrt();
            image.assign(i, h - 1 - j, ppm(col));
        }
    }
    image.output(filename);
}

Eigen::Vector3d Camera::color(const Ray &r, const Scene &world)
{
    HitRecord rec;
    Eigen::Vector3d col;
    if (world.hit(r, 0.001, std::numeric_limits<double>::max(), rec))
    {
        Eigen::Vector3d target = rec.p + rec.normal + random_in_unit_sphere();
        Eigen::Vector3d d = target - rec.p;
        Ray reflected_ray(rec.p, d);
        return 0.5 * color(reflected_ray, world);
    }
    else
    {
        Eigen::Vector3d unit_direction = r.direction().normalized();
        double t = 0.5 * (unit_direction(1) + 1);
        return (t * Eigen::Vector3d(0.5, 0.7, 1.0)).array() + (1 - t);
    }
}

Eigen::Vector3i Camera::ppm(Eigen::Vector3d &col) { return (255.99 * col).cast<int>(); }

Ray Camera::get_ray(double u, double v)
{
    Eigen::Vector3d target = m_lower_left_corner + u * m_horizontal + v * m_vertical;
    return Ray(m_origin, target);
}

Eigen::Vector3d Camera::random_in_unit_sphere()
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
