#pragma once

#include "common.h"

class camera 
{
public:
    camera() 
    {
        auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;//ray起点到视口的距离

        //使用右手坐标系,ray看向-z, +y上, +x左
        origin = point3(0, 0, 0);//射线起点
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);//假设ray起点的投影在视口的中心, 求视口左下角坐标
    }

    ray get_ray(double u, double v) const 
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    point3 origin;//射线起点
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};