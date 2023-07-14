#pragma once

#include "rt_common.h"

class camera 
{
public:
    camera(point3 lookfrom,//look from point
        point3 lookat,//look at point
        vec3   vup, //up direction
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio) 
    {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        vec3 w = unit_vector(lookfrom - lookat);//+z
        vec3 u = unit_vector(cross(vup, w));//up y
        vec3 v = cross(w, u);//x

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    ray get_ray(double s, double t) const 
    {
        return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }

private:
    point3 origin;//ÉäÏßÆðµã
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};