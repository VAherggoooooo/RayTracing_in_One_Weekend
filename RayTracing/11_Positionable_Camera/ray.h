#pragma once

#include "vec3.h"

class ray 
{
public:
    ray() {}

    /// <summary>
    /// 获得ray
    /// </summary>
    /// <param name="origin">起点</param>
    /// <param name="direction">朝向</param>
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    /// <summary>
    /// 获得t时刻ray到达的坐标
    /// </summary>
    /// <param name="t">时刻</param>
    /// <returns>ray达到的坐标</returns>
    point3 at(double t) const 
    {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};