#pragma once
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

class Neuron
{
private:
	float *weights;
	void generateWeights(int dendtrites);
	float threshold;
public:
	Neuron(int dendrites);
	float processInfo(vector<float>& data, bool exact);
	void giveInfo(int dendrites);
};

Neuron::Neuron(int dendrites)
{
	weights = new float[dendrites];
	generateWeights(dendrites);
}

void Neuron::generateWeights(int dendrites)
{
	for (int i = 0;i < dendrites;i++)
		weights[i] = (rand()%10000 / 10000.0);
	threshold = rand()%10000 / 10000.0;
}

float Neuron::processInfo(vector<float>& data, bool exact)
{
	float inputSum=0.0;
	for (int i = 0;i < data.size();i++)
	{
		inputSum += data[i] * weights[i];	
	}

	if (!exact)
	{
		if (inputSum > threshold)
			return 1.0;
		else
			return 0.0;
	}
	return inputSum;
}

void Neuron::giveInfo(int dendrites)
{
	cout << "Weights: ";

	for (int i = 0;i < dendrites;i++)
	{
		cout << weights[i] << " ";
	}
	cout << endl;
	cout << "Threshold: " << threshold << endl;
}
