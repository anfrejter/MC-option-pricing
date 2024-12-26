#include "gen_rand.h"
#include <cmath>
#include <cstdlib>
#include <string>

//Marsaglia polar method for generating random numbers - modified Box-Muller method
double generate_rand_norm()
{
	double result;

	double x;
	double y;

	double size_squared;
	do
	{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		size_squared = x * x + y * y;
	} while (size_squared >= 1.0);

	result = x * sqrt(-2 * log(size_squared) / size_squared);

	return result;
}
