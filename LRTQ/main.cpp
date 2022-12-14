#pragma once

//Libraries provided from RTinOneWeekend
#include "Color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

double sphere_hit(const point3& center, double radius, const ray& r) {
	
	// This works, but anything behind the image will mirror positive. That's bad.
	
	// oc = origin - center of the sphere
	vec3 oc = r.origin() - center;

	// A = direction squared
	auto a = dot(r.direction(), r.direction());

	auto b = 2.0 * dot(oc, r.direction());

	// C = OC squared - radius squared
	auto c = dot(oc, oc) - radius * radius;

	// discriminant = b*b - 4ac. Nothing really special.
	auto discriminant = b * b - (4 * a * c);
	
	//If we treat the discriminant as a unit vector, it makes things easier, I think.

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

color ray_colour(const ray& r) {
	
	// If sphere_hit > 0, colour using colour vector
	auto t = sphere_hit(point3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	//Tricks to normalise vector and write a gradient
	vec3 unit_dir = unit_vector(r.direction());
	t = 0.5 * (unit_dir.y() + 1.0);
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
	for (int j = height - 1; j >= 0; --j) {
		
		// This isn't working properly. TODO: fix it
		std::cerr << "\rLines Left to render" << j << "" << std::flush;
		for (int i = 0; i < width; ++i) {
			
			
			auto u = double(i) / (width - 1);
			auto v = double(j) / (height - 1);
			
			//
			ray r(origin, lower_left + u * horizontal + v * vertical - origin);
			color pixel_color = ray_colour(r);
			write_color(std::cout, pixel_color);
		}
	}
}