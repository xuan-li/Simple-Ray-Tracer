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
            
            std::vector<Eigen::Vector3i> cols(ns);
#pragma omp parallel
            {
#pragma omp for
                for (int s = 0; s < ns; ++s)
                {
                    // (u, v) is the screen coordinate of the intersection of the ray and the screen.
                    double u = double(i + rand() / (double(RAND_MAX) + 1.0)) / double(w);
                    double v = double(j + rand() / (double(RAND_MAX) + 1.0)) / double(h);
                    Ray r = get_ray(u, v);
                    cols[s] = color(r, world);
                }
            }

			Eigen::Vector3i col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                col += cols[s];
			}
            col /= ns;
            image.assign(i, h - 1 - j, col);
        }
    }
    image.output(filename);
}

Eigen::Vector3i Camera::color(const Ray &r, const Scene &world)
{
    HitRecord rec;
    Eigen::Vector3d col;
    if (world.hit(r, 0.0, std::numeric_limits<double>::max(), rec))
    {
        col = 0.5 * (rec.normal.array() + 1);
    }
    else
    {
        Eigen::Vector3d unit_direction = r.direction().normalized();
        double t = 0.5 * (unit_direction(1) + 1);
        col = (t * Eigen::Vector3d(0.5, 0.7, 1.0)).array() + (1 - t);
    }
    return (255.99 * col).cast<int>();
}

Ray Camera::get_ray(double u, double v)
{
    Eigen::Vector3d target = m_lower_left_corner + u * m_horizontal + v * m_vertical;
    return Ray(m_origin, target);
}
