#include "GlobalFunction.h"

unsigned int v2to1(unsigned int x, unsigned int y, unsigned int div_x)
{
	return x % (div_x + 1) + y * (div_x + 1);
}
