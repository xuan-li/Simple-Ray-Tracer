#include <ImageIO.h>
#include <Scene.h>
#include <limits.h>

Scene::Scene() {}

Scene::~Scene() {}

bool Scene::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (auto &h : m_hitable_list)
    {
        if (h->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
