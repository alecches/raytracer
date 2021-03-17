#pragma once
#include "Camera.h"
#include <mutex>

void renderSinglePixel(Color&, int x, int y, Ray, World);
Canvas2 renderMultithreaded(const Camera&, const World&);
Canvas renderParallel(const Camera&, const World&);
