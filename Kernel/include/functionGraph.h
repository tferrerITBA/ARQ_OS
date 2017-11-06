#include "videoMode.h"

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

void mathFunc(double a, double b, double c);

int validScreenCoordinate(int xCoord, int yCoord);

void paintSurroundingPixels(int xCenter, int yCenter);

int round(double value);

void paintAxis();