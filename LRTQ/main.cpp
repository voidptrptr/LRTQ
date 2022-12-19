#pragma once

//Libraries provided from RTinOneWeekend
#include "Color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

color ray_colour(const ray& r) {
	vec3 unit_dir = unit_vector(r.direction());
	auto t = 0.5 * (unit_dir.y() + 1.0);
	return(1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main() {


	//Consts for camera
	const auto aspect_ratio = 16 / 9;

	// Define constants for image size
	const int width = 400;
	const int height = static_cast<int>(width / aspect_ratio);

	//viewport
	const auto view_height = 2.0;
	const int view_width = view_height * aspect_ratio;
	const auto focal_length = 1;
	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(view_width, 0, 0);
	auto vertical = vec3(0, view_height, 0);
	auto lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//Init ppm 
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	//Write image data to buffer
	for (int j = height - 1; j > 0; --j) {
		std::cerr << "\rLines Left to render" << j << "" << std::flush;
		for (int i = 0; i < width; ++i) {
			auto u = double(i) / (width - 1);
			auto v = double(j) / (height - 1);
			ray r(origin, lower_left + u * horizontal + v * vertical - origin);
			color pixel_color = ray_colour(r);
			write_color(std::cout, pixel_color);
		}
	}
}