#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <Eigen/Eigen>
#include <iostream>
#include <memory>

class Image
{
  public:
    Image();
    Image(int w, int h);
    ~Image() {}
    void output(std::string filename);
    void assign(int w, int h, Eigen::Vector3i &color);
    int width() { return data.size(); }
    int height() { return data.front().size(); }

  private:
    std::vector<std::vector<Eigen::Vector3i>> data;
};

Image::Image() {}

#endif // !IMAGEIO_H
