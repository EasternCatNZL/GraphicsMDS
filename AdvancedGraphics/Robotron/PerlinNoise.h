#pragma once
#ifndef PerlinNoise_H
#define PerlinNoise_H

#include <vector>
#include "Utils.h"

class PerlinNoise {
public:
	PerlinNoise();
	//generate permutation vector based on value of seed
	PerlinNoise(int randomSeed);
	//get noise value, for 2d z can be any value
	float Noise(float x, float y, float z);
	float OctavePerlinNoise(float x, float y, float z, int octaves, float persistance);
	void createVerticesAndIndices();

private:
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Gradient(int hash, float x, float y, float z);
	int Increment(int num);

private:
	std::vector<int> permutationVector;
	std::vector<VertexFormat> verticesVector;
	int repeat = -1;
	GLfloat cellSpacing = 1.0f;
};

#endif // !PerlinNoise_H
