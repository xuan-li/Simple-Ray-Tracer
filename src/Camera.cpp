#include "Camera.h"
#include "Utilities.h"
#include <memory>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592654
#endif // !M_PI


Camera::Camera(Eigen::Vector3d lookfrom, Eigen::Vector3d lootat, Eigen::Vector3d vup, double vfov, double aspect, double aperture, double focus_dist)
{
    using namespace Eigen;
    
	
    double theta = vfov * M_PI / 180;
    double half_height = tan(theta / 2);
    double half_width = aspect * half_height;
    m_origin = lookfrom;
    backward = (lookfrom - lootat).normalized();
    vertical_right = vup.cross(backward).normalized();
    vertical_up = backward.cross(vertical_right);
    m_lower_left_corner = m_origin - half_width * vertical_right - half_height * vertical_up - focus_dist * backward;
    m_horizontal = 2 * half_width * vertical_right;
    m_vertical = 2 * half_height * vertical_up;

	lens_radius = aperture / 2;
}

Camera::~Camera() {}

void Camera::take_photo(std::string filename, const Scene &world, int w, int h, int ns)
{
    Image image(w, h);

    std::vector<double> us(ns);
    std::vector<double> vs(ns);
    for (int s = 0; s < ns; ++s)
    {
        us[s] = random01();
        vs[s] = random01();
    }

    for (int j = h - 1; j >= 0; --j)
        for (int i = 0; i < w; ++i)
        {

            std::vector<Eigen::Vector3d> cols(ns);
#pragma omp parallel for
            for (int s = 0; s < ns; ++s)
            {
                // (u, v) is the screen coordinate of the intersection of the ray and the screen.
                Ray r = get_ray(double(i + us[s]) / double(w), double(j + vs[s]) / double(h));
                cols[s] = color(r, world);
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
    image.output(filename);
}
Eigen::Vector3d Camera::color(const Ray &r, const Scene &world, int depth)
{
    HitRecord rec;
    Eigen::Vector3d col;
    if (world.hit(r, 0.001, std::numeric_limits<double>::max(), rec))
    {
        Ray scattered;
        Eigen::Vector3d attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation.cwiseProduct(color(scattered, world, depth + 1));
        else
            return Eigen::Vector3d(0, 0, 0);
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
    Eigen::Vector3d rd = lens_radius * random_in_unit_sphere();
    Eigen::Vector3d offset = vertical_right * rd(0) + vertical_up * rd(1); 
    Eigen::Vector3d direction = m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin - offset;
    return Ray(m_origin + offset, direction);
}