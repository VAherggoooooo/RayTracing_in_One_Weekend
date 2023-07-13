#pragma once

#include "rt_common.h"

vec3 reflect(const vec3& v, const vec3& n);

class material 
{
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian : public material 
{
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
    {
        if (rec.mat_ptr == nullptr) return false;
        auto scatter_direction = rec.normal + random_in_hemisphere(rec.normal);//射到材质表面后的一个随机漫反射方向
        //如果随机到的向量与法线的和近乎于零向量, 则反射方向就设定为法线方向
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;// *dot(unit_vector(rec.normal), unit_vector(scatter_direction));
        return true;
    }

public:
    color albedo;
};


class metal : public material 
{
public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
    double fuzz;
};