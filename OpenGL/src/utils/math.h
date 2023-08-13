#pragma once
# define M_PI 3.14159265358979323846
#include <iostream>
#include <cmath>
#include "../node.h"
std::pair<float, float> rotatePoint(float x, float y, float centerx, float centery, float angle);// Function to rotate a 2D point (x, y) by an angle theta (in radians)
std::pair<float, float> interpolate(float startx, float starty, float endx, float endy, double t);//calculate the next position from (a,b) to (c,d)
std::shared_ptr<allpurposenode> findMiddleOfList(std::shared_ptr<allpurposenode> head);
std::shared_ptr<allpurposenode> findRandomNodeOfList(std::shared_ptr<allpurposenode> head);