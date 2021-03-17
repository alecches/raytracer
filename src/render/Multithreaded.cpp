#include "Multithreaded.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <execution>
#include <stack>

//void renderSinglePixel(std::mutex& m, Color& color, int x, int y, Ray r, const World& w) {
void renderSinglePixel(Color& color, int x, int y, Ray r, World w) {
	
	color = colorAt(w, r);
	color.clampRGB();
	
}

void renderPixels(std::mutex& m, Canvas2& c, World w) {

	std::unique_lock<std::mutex> lck {m};
	Pixel* pixel = c.getPixelRef();
	lck.unlock();
	while (pixel != nullptr) {

		(*pixel).c = colorAt(w, (*pixel).r);
		(*pixel).c.clampRGB();

		lck.lock();
		pixel = c.getPixelRef();
		lck.unlock();
	} 
}

void renderPixelGroup(std::vector<Pixel*>& pixelGroup, World w) {

}

Canvas2 renderMultithreaded(const Camera& c, const World& w) {

	int numThreads = 3;
	int width = c.hsize();
	int height = c.vsize();
	Canvas2 image(width, height);
	std::vector<std::thread> threads;
	std::mutex m;

	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.assignRay(x, y, c.rayForPixel(x, y));
		}
	}

	auto t0 = std::chrono::high_resolution_clock::now();
	//
	for (int i = 0; i < numThreads; i++) {
		threads.push_back(std::thread(renderPixels, std::ref(m), std::ref(image), w));
	}
	//
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Calling the threads: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "msec" << std::endl;
	

	auto t2 = std::chrono::high_resolution_clock::now();
	//
	for (auto&& i : threads) {
		i.join();
	}
	//
	auto t3 = std::chrono::high_resolution_clock::now();
	std::cout << "Waiting on joins: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << "msec" << std::endl;

	return image;
}

void renderPixel(std::pair<Color&, Ray>& pixel, const World& w) {
	pixel.first = colorAt(w, pixel.second);
	pixel.first.clampRGB();
}

Canvas renderParallel(const Camera& c, const World& w) {
	int width = c.hsize();
	int height = c.vsize();
	Canvas image(width, height);
	std::vector<std::pair<Color&, Ray>> pixels;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixels.push_back(std::pair<Color&, Ray>(image.getPixelRef(x, y), c.rayForPixel(x, y)));
		}
	}

	std::for_each(std::execution::par, pixels.begin(), pixels.end(), [w](auto& elem) {
		renderPixel(elem, w);
		});

	return image;
}


