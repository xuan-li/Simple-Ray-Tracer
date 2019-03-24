#ifndef RAY_H
#define RAY_H
#include <Eigen/Eigen>

class Ray
{
  public:
    Ray(){};
    Ray(const Eigen::Vector3d &o, Eigen::Vector3d &d) : m_origin(o), m_direction(d){};
    Eigen::Vector3d origin() const { return m_origin; }
    Eigen::Vector3d direction() const { return m_direction; }
    Eigen::Vector3d point_at_parameter(double t) const { return m_origin + t * m_direction; }
    ~Ray(){};

  private:
    Eigen::Vector3d m_origin;
    Eigen::Vector3d m_direction;
};

#endif
