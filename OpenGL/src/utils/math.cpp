#include "math.h"
#include "./global.h"
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
std::pair<float,float> simulateBulletTrajectory(float startx, float starty, float endx, float endy, double initialVelocity, double timeInterval) {
    double angle = atan2(endy - starty, endx - startx);
    //for (double t = 0; t <= 1.0; t += timeInterval) {
        double x = startx + initialVelocity * cos(angle) * timeInterval;
        double y = starty + initialVelocity * sin(angle) * timeInterval - 0.5 * 9.81 * pow(timeInterval, 2);
        return { x, y };

        // Print the current position of the bullet
        //std::cout << "Time: " << t << " seconds | Position: (" << currentPosition.x << ", " << currentPosition.y << ")" << std::endl;

        // Simulate the passage of time
        //std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeInterval * 1000)));
    //}
};
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
            return cur;
        }
        k++;
        cur = cur->getter().next;
    }
    return cur;
};

// pass in scaling factor to adjust the distance between each layer
std::vector < std::pair<float, float>> fibonaccispiral(int numPoints, float centerx, float centery) {
    double goldenRatio = 1.61803398875;
    double angle = 0.0;
    double targetDistance = default_radius*2; // Adjust as needed
    double k = 1.0 / (goldenRatio * 3.14); // Adjust as needed
    double angleIncrement = 0.1; // Adjust as needed
    std::vector < std::pair<float, float>> res;
    for (int i = 0; i < numPoints; ++i) {
        double radius = exp(angle / (goldenRatio * 3.14)); // Adjust as needed
        float x = centerx + radius * cos(angle);
        float y = centery + radius * sin(angle);
        if (x < default_radius || y < default_radius || x >= logicalWidth - default_radius || y >= logicalHeight - default_radius) {
           break;
        }
        res.push_back({ x,y });
        double angleIncrement = targetDistance / exp(k * angle);
        angle += angleIncrement;
    }
    return res;
}
char randomcolorgenerator() {
    int random = rand() % 6;//random number between 0 and 5
    char t = 'G';//0
    if (random == 1) t = 'B';
    else if (random == 2) t = 'Y';
    else if (random == 3) t = 'W';
    else if (random == 4) t = 'O';
    else if (random == 5) t = 'V';
    return t;
};
