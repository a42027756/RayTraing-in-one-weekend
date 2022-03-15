//#include<iostream>
//#pragma comment(linker, "/STACK:102400000,102400000")
//
//
//#include"rtweekend.h"
//#include"color.h"
//#include"hittable_list.h"
//#include"sphere.h"
//#include "camera.h"
//
//using std::cin;
//using std::cout;
//
//
//color ray_color(const ray& r, const hittable& world) {
//	hit_record rec;
//	if (world.hit(r, 0, infinity, rec)) {
//		return 0.5 * (rec.normal + color(1, 1, 1));
//	}
//	vec3 unit_direction = unit_vector(r.direction());
//	double t = 0.5 * (unit_direction.y() + 1.0);
//	//线性插值
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//
//
//}
//
////Whitted Style ray tracing (I guess)
////color ray_color(const ray& r, const hittable& world, int depth) {
////	hit_record rec;
////	if (depth <= 0)
////		return color(0, 0, 0);
////	if (world.hit(r, 0.01, infinity, rec)) {
////		//point3 target = rec.p + rec.normal + random_in_unit_sphere();//随机点S
////		point3 target = rec.p + rec.normal + random_unit_vector();//随机点S Lambertian
////		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
////	}
////	vec3 unit_direction = unit_vector(r.direction());
////	double t = 0.5 * (unit_direction.y() + 1.0);
////	//线性插值
////	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
////}
//
//const int max_depth = 50;
//
//color ray_color(const ray& r, const hittable& world, int depth) {
//	hit_record rec;
//	if (depth <= 0)
//		return color(0, 0, 0);
//	if (world.hit(r, 0.001, infinity, rec)) {
//		ray scattered;
//		color attenuation;
//		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
//			return attenuation * ray_color(scattered, world, depth - 1);
//		return color(0, 0, 0);
//	}
//	
//	vec3 unit_direction = unit_vector(r.direction());
//	double t = 0.5 * (unit_direction.y() + 1.0);
//	//线性插值
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//}
//
//hittable_list random_scene() {
//	hittable_list world;
//
//	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
//	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));
//
//	for (int a = -11; a < 11; a++) {
//		for (int b = -11; b < 11; b++) {
//			auto choose_mat = random_double();
//			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
//
//			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
//				shared_ptr<material> sphere_material;
//
//				if (choose_mat < 0.8) {
//					// diffuse
//					auto albedo = color::random() * color::random();
//					sphere_material = make_shared<lambertian>(albedo);
//					world.add(make_shared<sphere>(center, 0.2, sphere_material));
//				}
//				else if (choose_mat < 0.95) {
//					// metal
//					auto albedo = color::random(0.5, 1);
//					auto fuzz = random_double(0, 0.5);
//					sphere_material = make_shared<metal>(albedo, fuzz);
//					world.add(make_shared<sphere>(center, 0.2, sphere_material));
//				}
//				else {
//					// glass
//					sphere_material = make_shared<dielectric>(1.5);
//					world.add(make_shared<sphere>(center, 0.2, sphere_material));
//				}
//			}
//		}
//	}
//
//	auto material1 = make_shared<dielectric>(1.5);
//	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
//
//	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
//	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
//
//	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
//	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
//
//	return world;
//}
//
//
//int main() {
//	//Image
//	//const double aspect_ratio = 16.0 / 9.0;
//	const auto aspect_ratio = 3.0 / 2.0;
//	//const int image_width = 400;
//	const int image_width = 1200;
//	const int image_height = static_cast<int>(image_width / aspect_ratio);
//	//const int image_height = 1800;
//	int samples_per_pixel = 100; //抗锯齿采样数
//	//World
//	////hittable_list world;
//	////world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
//	////world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); //背景的绿色，看起来像地板，其实是一个很大的球体
//	//hittable_list world;
//	//auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
//	//auto material_center = make_shared<lambertian>(color(0.7, 0.8, 0.3));
//	////auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
//	//auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
//	////auto material_right = make_shared<dielectric>(1.5);
//	//auto material_left = make_shared<dielectric>(1.5);
//
//	//world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
//	//world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
//	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
//	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
//	//world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
//	auto world = random_scene();
//
//	//Camera
//	//camera cam(point3(-2, 2, 1), point3(0, 0, -1), 20, aspect_ratio);
//	//camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0,1,0), 80, aspect_ratio);
//	//camera cam;
//	point3 lookfrom(13, 2, 3);
//	point3 lookat(0, 0, 0);
//	auto dist_to_focus = 10.0;
//	auto aperture = 0.1;
//
//	camera cam(lookfrom, lookat, 20, aspect_ratio, aperture, dist_to_focus);
//	ray r;
//	//Render
//	FILE* fp = fopen("final-render.png", "wb");
//	unsigned char rgb[image_width * image_height * 3], * p = rgb;
//	//unsigned char* p = new unsigned char[image_width * image_height * 3];
//	cout << "P3\n" << image_width << " " << image_height << "\n255\n";
//	for (int j = image_height - 1; j >= 0; --j) {
//		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//		for (int i = 0; i < image_width; ++i) {
//			/*double u = double(i) / (image_width - 1);
//			double v = double(j) / (image_height - 1);
//			r = cam.get_ray(u, v);
//			color pixel_color = ray_color(r, world);
//			write_color(p, pixel_color);*/
//			color pixel_color = vec3(0, 0, 0);
//			//Antialiasing 抗锯齿
//			for (int k = 0; k < samples_per_pixel; ++k)
//			{
//				// 向每个像素的右下方[0,1]范围内采样
//				auto u = (i + random_double()) / image_width; 
//				auto v = (j + random_double()) / image_height;
//				r = cam.get_ray(u, v);
//				pixel_color += ray_color(r, world, max_depth);
//			}
//			write_color(p, pixel_color, samples_per_pixel);
//			//write_color(cout, pixel_color, samples_per_pixel);
//			
//
//
//		}
//	}
//	std::cerr << "\nDone.\n";
//	svpng(fp, image_width, image_height, rgb, 0);
//	//delete[] p;
//	fclose(fp);
//}
