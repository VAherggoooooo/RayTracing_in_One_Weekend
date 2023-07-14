#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable 
{
public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m): center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    vec3 oc = r.origin() - center;
    //�����abc�Ƕ�Ԫһ�η��̵�ϵ��(At^2 + Bt + C = 0)
    //half_b��b/2, ���̼򻯰�
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;//��Ԫһ�κ�����delta
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;//����С���Ǹ�t
    if (root < t_min || t_max < root)//����Ͻ���t�ڸ�����Χ��
    {
        root = (-half_b + sqrtd) / a;//�ҽϴ��t
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);//�����߱���ͷ, ��ѷ��߷�ת
    rec.mat_ptr = mat_ptr;

    return true;
}

