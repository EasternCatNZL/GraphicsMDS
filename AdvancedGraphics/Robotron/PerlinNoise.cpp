#include "PerlinNoise.h"

#include <numeric>
#include <random>
#include <algorithm>
#include <numeric>


PerlinNoise::PerlinNoise(int randomSeed)
{
	//change size of vector
	permutationVector.resize(256);
	//fill vector with values from 0 to 255
	std::iota(permutationVector.begin(), permutationVector.end(), 0);
	//initialize a random seed
	std::default_random_engine engine(randomSeed);
	//shuffle vector using random engine
	std::shuffle(permutationVector.begin(), permutationVector.end(), engine);
	//duplicate vector
	permutationVector.insert(permutationVector.end(), permutationVector.begin(), permutationVector.end());
}
