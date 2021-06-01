#pragma once
#include <random>
#include <time.h>
using namespace std;

// You should only have one RandGen object in your program.
// It should not be declared inside a loop or inside a function that is called more than once.


class RandGen
{
public:
	RandGen()
	{
		setSeed((int)time(NULL));
	}
	RandGen(int x)
	{
		setSeed(x);
	}
	void setSeed(int seed)
	{
		pEngine = new mt19937_64(seed);
	}
	double getDouble(double lowRange, double highRange)
	{
		uniform_real_distribution<double> dist(lowRange, highRange);
		return dist(*pEngine);
	}
	int getInt(int lowRange, int highRange)
	{
		uniform_int_distribution<int> dist(lowRange, highRange);
		return dist(*pEngine);
	}
private:
	mt19937_64 * pEngine;
};
