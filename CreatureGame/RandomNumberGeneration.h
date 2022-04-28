#pragma once
#include <cstdlib>	//for rand() and srand()
#include <ctime>	//for time()

// Generate a random number between min and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX


namespace random {
	int getRandomNumber(int min, int max);
}