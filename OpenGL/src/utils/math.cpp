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

// pass in Center of the spiral, radious, angle, Number of spiral arms
std::vector < std::pair<float, float>> fibonaccispiral(double centerX, double centerY, int screenWidth, int screenHeight, double radius, double angle, int arms) {
    double goldenRatio = (1.0 + std::sqrt(5.0)) / 2.0;
    // Number of points in each arm
    int pointsPerArm = 500;
    // Angle increment for each point
    double angleIncrement = 2.0 * M_PI * (1.0 - 1.0 / goldenRatio);
    std::vector < std::pair<float, float>> res;
    // Draw the Fibonacci spiral
    for (int arm = 0; arm < arms; ++arm) {
        for (int i = 0; i < pointsPerArm; ++i) {
            double x = centerX + radius * std::cos(angle);
            double y = centerY - radius * std::sin(angle); // Negative sin to invert the y-axis
            if (x < 0 || y < 0 || x >= grid[0].size() || y >= grid.size()) break;
            // Draw point (you might use a graphics library like SFML or OpenGL for this)
            res.push_back({x,y});

            angle += angleIncrement;
            radius *= goldenRatio;
        }
    }
    return res;
}
