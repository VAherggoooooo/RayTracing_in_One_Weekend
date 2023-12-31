#include "rt_common.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include <iostream>

using namespace std;

color ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;//记录ray击中信息
    
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);//反射的颜色
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);//225
    const int samples_per_pixel = 200;//每个像素采样的次数 抗锯齿参数 同样也可以改变光追质量
    const int max_depth = 15;//最多反弹深度(次数) 光追采样参数

    // World
    auto R = cos(pi / 4);
    hittable_list world;

    shared_ptr<lambertian> material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    shared_ptr<lambertian> material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    shared_ptr<dielectric> material_left = make_shared<dielectric>(1.5);
    shared_ptr<metal> material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    //camera
    //camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);
    camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 60, aspect_ratio);

    // Render
    cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) 
    {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) 
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) 
            {
                //每个像素都进行uv(轻度)偏移后采样来抗锯齿
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(cout, pixel_color, samples_per_pixel);
        }
    }
    cerr << "\nDone.\n";
}