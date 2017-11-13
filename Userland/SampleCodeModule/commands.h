#include <stdint.h>
#include "lib.h"
void runHelp();
void runClear();
void runZeroDiv();
void runOverflow();
void runInvOpc();
void runTime();
void runChcolor(uint8_t blue, uint8_t green, uint8_t red);
void runBgcolor(uint8_t blue, uint8_t green, uint8_t red);
void runMath(double a, double b, double c);
extern void raiseInvOp();
void colorFade(uint8_t from[], uint8_t to[]);
uint8_t getDistance(uint8_t a, uint8_t b);


