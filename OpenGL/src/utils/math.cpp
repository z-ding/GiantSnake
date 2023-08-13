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
std::pair<float, float> interpolate(float startx, float starty, float endx, float endy, double t) {
    float resultx;
    float resulty;
    resultx = startx + t * (endx - startx);
    resulty = starty + t * (endy - starty);
    return { resultx,resulty };
}
std::shared_ptr<allpurposenode> findMiddleOfList(std::shared_ptr<allpurposenode> head) {
    auto fast = head;
    auto slow = head;
    while (fast != nullptr) {
        fast = fast->getter().next;
        if (fast == nullptr) return slow;
        fast = fast->getter().next;
        slow = slow->getter().next;
    }
    return slow;
};
std::shared_ptr<allpurposenode> findRandomNodeOfList(std::shared_ptr<allpurposenode> head) {
    auto cur = head;
    int len = 0;
    while (cur != nullptr) {
        len++;
        cur = cur->getter().next;
    }
    int random = rand() % len;
    int k = 0;
    cur = head;
    while (k <= random) {
        if (k == random) {
            std::cout << "target" << cur << std::endl;
            return cur;
        }
        k++;
        cur = cur->getter().next;
    }
    return cur;
};
