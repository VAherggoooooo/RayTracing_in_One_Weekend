#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

bool hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = r.origin() - center;
    //这里的abc是二元一次方程的系数(At^2 + Bt + C = 0)
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;//delta, 看解的个数
    return (discriminant > 0);//是否有解? 有解则与球相交
}

color ray_color(const ray& r) 
{
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);//225

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;//32.0/9.0
    auto focal_length = 1.0;//ray起点到视口的距离

    //使用右手坐标系,ray看向-z, +y上, +x左
    auto origin = point3(0, 0, 0);//射线起点
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);//假设ray起点的投影在视口的中心, 求视口左下角坐标

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) 
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);//视口每一个坐标与ray起点的连线, 从起点出发
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}