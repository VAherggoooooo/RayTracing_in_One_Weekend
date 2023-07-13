#pragma once

#include "vec3.h"

class ray 
{
public:
    ray() {}

    /// <summary>
    /// ���ray
    /// </summary>
    /// <param name="origin">���</param>
    /// <param name="direction">����</param>
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    /// <summary>
    /// ���tʱ��ray���������
    /// </summary>
    /// <param name="t">ʱ��</param>
    /// <returns>ray�ﵽ������</returns>
    point3 at(double t) const 
    {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};