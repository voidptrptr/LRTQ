#pragma once

//Libraries provided from RTinOneWeekend
#include "Color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

int main() {
	// Define constants for image size
	const int width = 256;
	const int height = 256;

	//Init ppm 
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	//Write image data to buffer
	for (int j = height - 1; j > 0; --j) {
		std::cerr << "\rLines Left to render" << j << "" << std::flush;
		for (int i = 0; i < width; ++i) {
			color pixel_color(double(i) / (width - 1), double(j) / (height - 1), 0.25);
			write_color(std::cout, pixel_color);
		}
	}
}