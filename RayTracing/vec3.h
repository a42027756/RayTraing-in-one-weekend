#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <math.h>
#include "rtweekend.h"

using namespace std;
using std::sqrt;


class vec3 {
public:
	vec3() : e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

	}

	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}

	double length() const {
		return sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}


public:
	double e[3];

};

//Type aliases for vec3 
using point3 = vec3;
using color = vec3;

inline void operator<< (unsigned char *&out, const vec3 & v)
{
	*out++ = (unsigned char)(v.e[0]); //r
	*out++ = (unsigned char)(v.e[1]); //g
	*out++ = (unsigned char)(v.e[2]); //b

}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}


//在单位球体中取随机点
vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		//如果p的长度大于1（即半径大于1，不在球体内）就继续循环
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

//折射
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return (r_out_perp + r_out_parallel);
}

//vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
//    auto cos_theta = dot(-uv, n);
//    vec3 r_out_parallel =  etai_over_etat * (uv + cos_theta*n);
//    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
//    return r_out_parallel + r_out_perp;
//}

//inline vec3 refract(const vec3& v, const vec3& n, double ni_over_nt) {
//	vec3 uv = unit_vector(v);
//	float dt = dot(uv, n);
//	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
//  return (ni_over_nt * (uv - n * dt) - n * sqrt(discriminant));
//}






#endif // ! VEC3.H
