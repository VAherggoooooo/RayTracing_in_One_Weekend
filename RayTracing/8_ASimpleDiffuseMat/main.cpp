#include "rt_common.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>

using namespace std;

color ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;//记录ray击中信息
    
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
    const int samples_per_pixel = 800;//每个像素采样的次数 抗锯齿参数 同样也可以改变光追质量
    const int max_depth = 300;//最多反弹深度(次数) 光追采样参数

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam;

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