#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "material.h"
#include "ray.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double rad, shared_ptr<material> m) : center(cen), radius(rad), mat_ptr(m) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;

};


//bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
//{
//	vec3 oc = r.origin() - center;
//	double a = r.direction().length_squared();
//	double half_b = dot(r.direction(), oc);
//	double c = oc.length_squared() - radius * radius;
//	double discriminant = half_b * half_b - a * c;
//	if (discriminant > 0) {
//		double root = sqrt(discriminant);
//		double t = (-half_b - root) / a;
//		if (t > t_min && t < t_max) {
//			rec.t = t;
//			rec.p = r.at(t);
//			vec3 outward_normal = (rec.p - center) / radius;
//			rec.set_face_normal(r, outward_normal);
//			rec.mat_ptr = mat_ptr;
//			//rec.normal = (rec.p - center) / radius;
//
//			return true;
//		}
//		t = (-half_b + root) / a;
//		if (t > t_min && t < t_max) {
//			rec.t = t;
//			rec.p = r.at(t);
//			rec.normal = (rec.p - center) / radius;
//			rec.mat_ptr = mat_ptr;
//
//			return true;
//		}
//	}
//	return false;
//}

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
#endif // !SPHERE_H
