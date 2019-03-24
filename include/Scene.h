#ifndef SCENE_H
#define SCENE_H

#include <Sphere.h>

class Scene:public Hitable
{
  public:
    Scene();
    ~Scene();
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
    int list_size() const { return m_list_size; }
    void add_object(std::shared_ptr<Hitable> object) { m_hitable_list.push_back(object); }

  private:
    int m_list_size;
    std::vector<std::shared_ptr<Hitable>> m_hitable_list;
    
};


#endif
