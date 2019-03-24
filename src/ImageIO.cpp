#include <ImageIO.h>
#include <fstream>;

Image::Image(int w, int h) { data.resize(h, std::vector<Eigen::Vector3i>(w)); }

void Image::output(std::string filename)
{
    using namespace Eigen;
    using namespace std;
    int w = width();
    int h = height();

    ofstream f(filename);
    f << "P3" << endl;
    f << w << " " << h << endl;
    f << "255" << endl;
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            f << data[j][i].transpose() << endl;
        }
    }
    f.close();
}

void Image::assign(int w, int h, Eigen::Vector3i &color) { data[h][w] = color; }
