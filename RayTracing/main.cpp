#include<iostream>

#include"rtweekend.h"
#include"color.h"
#include"hittable_list.h"
#include"sphere.h"
#include "camera.h"

using std::cin;
using std::cout;


color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	//���Բ�ֵ
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);


}

//Whitted Style ray tracing (I guess)
//color ray_color(const ray& r, const hittable& world, int depth) {
//	hit_record rec;
//	if (depth <= 0)
//		return color(0, 0, 0);
//	if (world.hit(r, 0.01, infinity, rec)) {
//		//point3 target = rec.p + rec.normal + random_in_unit_sphere();//�����S
//		point3 target = rec.p + rec.normal + random_unit_vector();//�����S Lambertian
//		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
//	}
//	vec3 unit_direction = unit_vector(r.direction());
//	double t = 0.5 * (unit_direction.y() + 1.0);
//	//���Բ�ֵ
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//}

const int max_depth = 50;

color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;
	if (depth <= 0)
		return color(0, 0, 0);
	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	//���Բ�ֵ
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main() {
	//Image
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	int samples_per_pixel = 10; //����ݲ�����
	//World
	//hittable_list world;
	//world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	//world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); //��������ɫ����������ذ壬��ʵ��һ���ܴ������
	hittable_list world;
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.7, 0.8, 0.3));
	//auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
	//auto material_right = make_shared<dielectric>(1.5);
	auto material_left = make_shared<dielectric>(1.5);

	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	//Camera
	camera cam;
	ray r;
	//Render
	FILE* fp = fopen("dieletrics_broken.png", "wb");
	unsigned char rgb[image_width * image_height * 3], * p = rgb;

	cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			/*double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			r = cam.get_ray(u, v);
			color pixel_color = ray_color(r, world);
			write_color(p, pixel_color);*/
			color pixel_color = vec3(0, 0, 0);
			//Antialiasing �����
			for (int k = 0; k < samples_per_pixel; ++k)
			{
				// ��ÿ�����ص����·�[0,1]��Χ�ڲ���
				auto u = (i + random_double()) / image_width; 
				auto v = (j + random_double()) / image_height;
				r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(p, pixel_color, samples_per_pixel);
			


		}
	}
	std::cerr << "\nDone.\n";
	svpng(fp, image_width, image_height, rgb, 0);
	//delete[] p;
	fclose(fp);
}
