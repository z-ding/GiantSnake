#include "math.h"
std::pair<float,float> rotatePoint(float x, float y, float centerx, float centery, float angle) {
    float x1;
    float y1;
    float cosA = cos(angle);
    float sinA = sin(angle);
    x -= centerx;
    y -= centery;
    x1 = x * cosA - y * sinA +centerx;
    y1 = x * sinA + y * cosA+centery;
    return { x1,y1 };
}