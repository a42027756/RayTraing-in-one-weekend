//#include <iostream>
//#include "svpng.inc"
//#include "vec3.h"
//#include "color.h"
//#include "ray.h"
//
//
////����
//double hit_sphere(const point3& center, double radius, const ray& r) {
//	//�ο���ʽ��b * b * t^2 + 2 * b * (A - C) * t + (A - C) * (A - C) - r^2 = 0
//	//����AΪ����λ�ã�bΪ���߷���CΪ��������ĵ�
//	vec3 oc = r.origin() - center;
//	double a = dot(r.direction(), r.direction());
//	double half_b = dot(r.direction(), oc);
//	double c = oc.length_squared() - radius * radius;
//	double discriminant = half_b * half_b - a * c;  //Delta�б�ʽ
//	if (discriminant < 0)
//		return -1.0;
//	else {
//		double t1 = (-half_b - sqrt(discriminant)) / a;
//		if (t1 > 0)
//			return t1;
//		double t2 = (-half_b + sqrt(discriminant)) / a;
//		if (t2 > 0)
//			return t2;
//		return -1.0;
//	}
//
//}
//
////��ֵ��ɫ
//color ray_color(const ray& r) {
//	//���߻��оͷ���t��ֵ��û�оͷ���-1
//	double t = hit_sphere(point3(0, 0, -1), 0.5, r);
//	if (t > 0) {
//		//���㷨�������������ĵ��ȥ���ĵ㣬����ָ�򱻼��� + ��λ��
//		vec3 N = unit_vector(r.at(t) - point3(0, 0, -1));
//		//��[-1, 1]ӳ�䵹[0��1]
//		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
//	}
//
//
//	//���߻��о���ʾ��ɫ
//	/*if (hit_sphere(point3(0, 0, -1), 0.5, r))
//	{
//		return color(1, 0, 0);
//	}*/
//	vec3 unit_direction = unit_vector(r.direction()); //��ȡ��λ����
//	t = 0.5 * (unit_direction.y() + 1.0); //
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//}
//
//
//
//int main() {
//
////first ppm
//    //// Image
//    //FILE* fp = fopen("firstppm.png", "wb");
//    //unsigned char rgb[256 * 256 * 3], * p = rgb;
//    //const int image_width = 256;
//    //const int image_height = 256;
//
//    //// Render
//
//    //for (int j = image_height - 1; j >= 0; --j) {
//    //    for (int i = 0; i < image_width; ++i) {
//    //        color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
//    //        write_color(p, pixel_color);
//    //    }
//    //}
//    //svpng(fp, 256, 256, rgb, 0);
//    //fclose(fp);
//    //return 0;
//	
//	//Image
//	const auto aspect_ratio = 16.0 / 9.0;
//	const int image_width = 400;
//	const int image_height = static_cast<int>(image_width / aspect_ratio);
//
//	//Camera
//	auto viewport_height = 2.0;
//	auto viewport_width = aspect_ratio * viewport_height;
//	auto focal_length = 1.0;
//
//	auto origin = point3(0, 0, 0);
//	auto horizontal = vec3(viewport_width, 0, 0);
//	auto vertical = vec3(0, viewport_height, 0);
//	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
//	
//	// Render
//
//	FILE* fp = fopen("sphere.png", "wb");
//	//ָ�������С [width height RGB/RGBA]
//	unsigned char rgb[image_width * image_height * 3], * p = rgb; //���ʽ���뺬�г���ֵ��������Ȼ��������
//	//unsigned char* p = new unsigned char[image_width * image_height * 3];
//
//	//std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
//
//	for (int j = image_height - 1; j >= 0; --j) {
//		for (int i = 0; i < image_width; ++i) {
//			auto u = double(i) / (image_width - 1);
//			auto v = double(j) / (image_height - 1);
//			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
//			color pixel_color = ray_color(r);
//			write_color(p, pixel_color);
//		}
//	}
//
//	svpng(fp, image_width, image_height, rgb, 0);
//	//delete[] p;
//	fclose(fp);
//	return 0;
//
//	/*std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
//
//	for (int j = image_height - 1; j >= 0; --j) {
//		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//		for (int i = 0; i < image_width; ++i) {
//			auto u = double(i) / (image_width - 1);
//			auto v = double(j) / (image_height - 1);
//			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
//			color pixel_color = ray_color(r);
//			write_color(std::cout, pixel_color);
//		}
//	}
//
//	std::cerr << "\nDone.\n";*/
//}