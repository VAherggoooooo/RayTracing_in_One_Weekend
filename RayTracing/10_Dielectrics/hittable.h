#pragma once

#include "rt_common.h"
#include "ray.h"

class material;

struct hit_record 
{
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat_ptr;

    /// <summary>
    /// ��ray���б���, ��ѷ�����������(��ѡ����)
    /// </summary>
    /// <param name="r"></param>
    /// <param name="outward_normal"></param>
    inline void set_face_normal(const ray& r, const vec3& outward_normal) 
    {
        front_face = dot(r.direction(), outward_normal) < 0;//front��ָ��(������ȫָ��)����ķ���
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable 
{
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};