#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable 
{
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;
    double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    vec3 oc = r.origin() - center;
    //这里的abc是二元一次方程的系数(At^2 + Bt + C = 0)
    //half_b是b/2, 方程简化版
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;//二元一次函数的delta
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;//求解较小的那个t
    if (root < t_min || t_max < root)//如果较近的t在给定范围外
    {
        root = (-half_b + sqrtd) / a;//找较大的t
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);//若法线背向镜头, 则把法线翻转

    return true;
}

