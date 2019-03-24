#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "ImageIO.h"
#include "Scene.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    void take_photo(std::string filename, const Scene &world);

	protected:
    Eigen::Vector3d color(const Ray &r, const Scene &world);
    Eigen::Vector3i ppm(Eigen::Vector3d &col);
    Ray get_ray(double u, double v);
    Eigen::Vector3d random_in_unit_sphere();


  private:
    Eigen::Vector3d m_lower_left_corner; // the screen position in the world coordinate system;
    Eigen::Vector3d m_horizontal;        // the screen horizontal span;
    Eigen::Vector3d m_vertical;          // the screen vertical span;
    Eigen::Vector3d m_origin;            // the origin of all rays, emit from the camera.
    int w;
    int h;
    int ns;
	
};


#endif // !CAMERA_H
