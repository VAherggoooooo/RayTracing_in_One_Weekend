#pragma once

#include "ray.h"

struct hit_record 
{
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    /// <summary>
    /// 若ray击中背面, 则把法线修正反向(可选函数)
    /// </summary>
    /// <param name="r"></param>
    /// <param name="outward_normal"></param>
    inline void set_face_normal(const ray& r, const vec3& outward_normal) 
    {
        front_face = dot(r.direction(), outward_normal) < 0;//front是指向(不是完全指向)相机的方向
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable 
{
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};