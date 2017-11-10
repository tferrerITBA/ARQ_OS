#include "functionGraph.h"

void mathFunc(double a, double b, double c) {
	/*
	** screenX is X offset from left
	** screenY is Y offset from bottom
	** x and y are function actual values
	*/

	int x;
	int y;
	int screenX;
	int screenY;

	paintAxis();

	for (x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x++) {
		y = round(a*x*x + b*x + c);
		screenX = x + SCREEN_WIDTH/2;
		screenY = SCREEN_HEIGHT/2 - y;
		if (validScreenCoordinate(screenX,screenY)) {
			paintSurroundingPixels(screenX, screenY);
		}
	}
}

int validScreenCoordinate(int xCoord, int yCoord) {
	if ((xCoord < SCREEN_WIDTH -1) && (xCoord > 0) && (yCoord > 0) && (yCoord < SCREEN_HEIGHT -1)) {
		return 1;
	}
	return 0;
}

void paintSurroundingPixels(int xCenter, int yCenter) {
	int j;
	int k;

	for(j = -1; j < 2 ; j ++) {
		for(k = -1; k < 2; k++) {
			pixelInt(xCenter + j, yCenter + k);
		}
	}
}

int round(double value) {
	int floor = (int) value;
	if(value - (double)floor < (double)(floor +1) - value) {
		return value;
	}
	return value + 1;
}

void paintAxis() {
	int i, j;
	for(i = 0; i < SCREEN_WIDTH; i++) {
		for(j = -1; j < 1; j++) {
			pixelInt(i, SCREEN_HEIGHT/2 + j);
		}
	}
	for(i = 0; i < SCREEN_HEIGHT; i++) {
		for(j = -1; j < 1; j++) {
			pixelInt(SCREEN_WIDTH/2 + j, i);
		}
	}
}

