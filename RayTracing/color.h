#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "svpng.inc"

#include <iostream>

void write_color(unsigned char *&out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    *out++ = (unsigned char)static_cast<int>(255.999 * pixel_color.x());
    *out++ = (unsigned char)static_cast<int>(255.999 * pixel_color.y());
    *out++ = (unsigned char)static_cast<int>(255.999 * pixel_color.z());
    return;
}

void write_color(std::ostream& out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	//根据样本数对颜色取平均值
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void write_color(unsigned char *&out, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	//根据样本数对颜色取平均值  此时传入的pixel_color是已经经过加权的
	auto scale = 1.0 / samples_per_pixel;

	//Gamma Correction
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);


	/*r *= scale;
	g *= scale;
	b *= scale;*/
	*out++ = (unsigned char)static_cast<int>(256 * clamp(r, 0.0, 0.999));
	*out++ = (unsigned char)static_cast<int>(256 * clamp(g, 0.0, 0.999));
	*out++ = (unsigned char)static_cast<int>(256 * clamp(b, 0.0, 0.999));
}

#endif