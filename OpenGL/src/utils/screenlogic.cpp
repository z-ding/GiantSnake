#include "screenlogic.h"
#include "global.h"
std::pair<float, float> logicalToScreenCoordinates(float logicalx, float logicaly) {
    float x = (logicalx / logicalWidth) * windowWidth;
    float y = (logicaly / logicalHeight) * windowHeight;
    return { x,y };
}