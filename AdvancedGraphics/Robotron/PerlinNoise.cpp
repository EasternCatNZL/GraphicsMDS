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

float PerlinNoise::Noise(float x, float y, float z)
{
	//calculate unit cube that the point will be located
	int xi = (int)x & 255;
	int yi = (int)y & 255;
	int zi = (int)z & 255;
	//calculate location in cube from 0.0 to 1.0
	float xf = x - (int)x;
	float yf = x - (int)y;
	float zf = x - (int)z;
	//fade location to smooth result
	float fadeX = Fade(xf);
	float fadeY = Fade(xf);
	float fadeZ = Fade(xf);

	//hashes 8 unit cuve co-ords surrounding input
	int aaa, aba, aab, abb, baa, bba, bab, bbb;

	aaa = permutationVector[permutationVector[permutationVector[xi] + yi] + zi];
	aba = permutationVector[permutationVector[permutationVector[xi] + Increment(yi)] + zi];
	aab = permutationVector[permutationVector[permutationVector[xi] + yi] + Increment(zi)];
	abb = permutationVector[permutationVector[permutationVector[xi] + Increment(yi)] + Increment(zi)];
	baa = permutationVector[permutationVector[permutationVector[Increment(xi)] + yi] + zi];
	bba = permutationVector[permutationVector[permutationVector[Increment(xi)] + Increment(yi)] + zi];
	bab = permutationVector[permutationVector[permutationVector[Increment(xi)] + yi] + Increment(zi)];
	bbb = permutationVector[permutationVector[permutationVector[Increment(xi)] + Increment(yi)] + Increment(zi)];

	//calculate the dot product between a pseudo random gradient vector and the vector from the input co-ord to 8 points of unit cube
	//lerp together as a sort of weighted average based on the faded x,y,z values
	float x1, x2, y1, y2;
	
	x1 = Lerp(Gradient(aaa, xf, yf, zf), Gradient(baa, xf - 1, yf, zf), fadeX);
	x2 = Lerp(Gradient(aba, xf, yf - 1, zf), Gradient(bba, xf - 1, yf - 1, zf), fadeX);

	y1 = Lerp(x1, x2, fadeY);

	x1 = Lerp(Gradient(aab, xf, yf, zf - 1), Gradient(bab, xf - 1, yf, zf - 1), fadeX);
	x2 = Lerp(Gradient(abb, xf, yf - 1, zf - 1), Gradient(bbb, xf - 1, yf - 1, zf - 1), fadeX);

	y2 = Lerp(x1, x2, fadeY);

	return (Lerp(y1, y2, fadeZ) + 1) / 2;
}

float PerlinNoise::OctavePerlinNoise(float x, float y, float z, int octaves, float persistance)
{
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0; // used for normalizing result between 0 and 1.0

	for (int i = 0; i < octaves; i++) {
		total += Noise(x * frequency, y * frequency, z * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistance;
		frequency *= 2;
	}

	return total / maxValue;
}

int PerlinNoise::Increment(int num)
{
	num++;
	if (repeat > 0) {
		num %= repeat;
	}
	return num;
}

//eases coordinate values so that they will ease towards integral values. smooth final output
//6t^5 - 15t^4 + 10t^3
float PerlinNoise::Fade(float t)
{
	return t * t * t *(t *(t * 6 - 15) + 10);
}

//linear interpolation
float PerlinNoise::Lerp(float t, float a, float b)
{
	return a + t * (b - a);
}

//calculate dot product of randomly selected gradient vector and 8 location vecot
float PerlinNoise::Gradient(int hash, float x, float y, float z)
{
	switch (hash & 0xF) {
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  x + z;
	case 0x5: return -x + z;
	case 0x6: return  x - z;
	case 0x7: return -x - z;
	case 0x8: return  y + z;
	case 0x9: return -y + z;
	case 0xA: return  y - z;
	case 0xB: return -y - z;
	case 0xC: return  y + x;
	case 0xD: return -y + z;
	case 0xE: return  y - x;
	case 0xF: return -y - z;
	default: return 0; // never happens
	}
}
