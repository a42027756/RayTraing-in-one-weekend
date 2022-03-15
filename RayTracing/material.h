#pragma once
#pragma comment(linker, "/STACK:102400000,102400000")
#ifndef  MATERIAL_H
#define  MATERIAL_H

#include "rtweekend.h"
//#include "hittable.h"

struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian :public material {
public:
	lambertian(const color& a) :albedo(a) { }

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		//漫反射材料 光线随机散射
		vec3 scatter_direction = rec.normal + random_unit_vector();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;

		
		return true;
	}
public:
	color albedo;
};

class metal :public material {
public:
	metal(const color& a, double f) :albedo(a), fuzz(f) { }

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		//金属材料 所有光线镜面反射
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		//将albedo直接设为衰减
		//可以这么理解：物体吸收一部分光线，剩下的反射出去，吸收的即为衰减光照，反射出去的就是albedo，即物体会显示出的颜色
		attenuation = albedo;
		//attenuation = vec3(0.5, 0.5, 0.5);
		return (dot(scattered.direction(), rec.normal) > 0);
	}
public:
	color albedo;
	double fuzz;
};

//class dielectric :public material {
//public:
//	dielectric(double ri) :ref_idx(ri) { }
//
//	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
//		//没有衰减，不吸收任何光线
//		attenuation = color(1.0, 1.0, 1.0);
//		//判断交点是在外部还是内部 front_face为true时-->外部
//		double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;
//		vec3 unit_direction = unit_vector(r_in.direction());
//		vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
//		scattered = ray(rec.p, refracted);
//		return true;
//	}
//public:
//	double ref_idx; //折射率?
//};

class dielectric : public material {
public:
	dielectric(double index_of_refraction) : ir(index_of_refraction) {}

	//inline bool refract(const ray& r_in, const vec3& n, double eta, ray& refracted) const
	//{
	//	vec3 unit_direction = unit_vector(r_in.direction());    //将入射光线单位化

	//	double cos1 = dot(unit_direction, n);
	//	double cos2 = 1. - eta * eta * (1. - cos1 * cos1);
	//	if (cos2 > 0)
	//	{
	//		refracted.direction() = eta * unit_direction + n * (eta * cos1 - sqrt(cos2));
	//		return true;
	//	}
	//	return false;
	//}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		//没有衰减，不吸收任何光线
		attenuation = color(1.0, 1.0, 1.0);
		//判断交点是在外部还是内部 front_face为true时-->外部
		double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
		//double refraction_ratio = ir;

		vec3 unit_direction = unit_vector(r_in.direction());
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio);
		//direction = refract(unit_direction, rec.normal, refraction_ratio); 
		//direction = reflect(unit_direction, rec.normal);


		scattered = ray(rec.p, direction);
		/*vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

		scattered = ray(rec.p, refracted);*/
		return true;
	}

public:
	double ir; // Index of Refraction

private:
	static double reflectance(double cosine, double ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

//class dielectric :public material
//{
//public:
//	dielectric(const rtvar RI) :_RI(RI) {  }
//
//	virtual bool scatter(const ray& InRay, const hitInfo& info, rtvec& attenuation, ray& scattered)const override;
//
//	inline bool refract(const rtvec& rIn, const rtvec& n, rtvar eta, rtvec& refracted)const
//	{
//		rtvec unitIn = rIn.ret_unitization();    //将入射光线单位化
//
//		rtvar cos1 = dot(unitIn, n);
//		rtvar cos2 = 1. - eta * eta * (1. - cos1 * cos1);
//		if (cos2 > 0)
//		{
//			refracted = eta * (rIn - n * cos1) - n * sqrt(cos2);
//			return true;
//		}
//		return false;
//	}
//private:
//	rtvar _RI;
//};
//
//bool dielectric::scatter(const ray& InRay, const hitInfo& info, rtvec& attenuation, ray& scattered)const
//{
//	rtvec outward_normal;
//	rtvec reflected = metal::reflect(InRay.direction(), info._n);
//	rtvar eta;
//	attenuation = rtvec(1., 1., 1.);
//	rtvec refracted;
//
//	if (dot(InRay.direction(), info._n) > 0)
//	{
//		outward_normal = -info._n;
//		eta = _RI;
//	}
//	else
//	{
//		outward_normal = info._n;
//		eta = 1. / _RI;
//	}
//	if (refract(InRay.direction(), outward_normal, eta, refracted))
//	{
//		scattered = ray(info._p, refracted);
//	}
//	else
//	{
//		scattered = ray(info._p, reflected);
//		return false;
//	}
//	return true;
//};

#endif // ! MATERIAL_H
