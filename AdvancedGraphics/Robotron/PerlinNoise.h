#pragma once
#ifndef PerlinNoise_H
#define PerlinNoise_H

#include <vector>

class PerlinNoise {
public:
	PerlinNoise();
	//generate permutation vector based on value of seed
	PerlinNoise(int randomSeed);
	//get noise value, for 2d z can be any value
	float Noise(float x, float y, float z);
	float OctavePerlinNoise(float x, float y, float z, int octaves, float persistance);
	int Increment(int num);

private:
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Gradient(int hash, float x, float y, float z);

private:
	std::vector<int> permutationVector;
	int repeat = -1;
};

#endif // !PerlinNoise_H
