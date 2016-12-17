#pragma once

#include <vector>

#include "neuron.h"

using namespace std;

class Layer
{
private:
	vector<Neuron> neurons;
	vector<float> outputData;
public:
	Layer(int dendriteNum, int neuronNum);
	vector<float> processData(vector<float>& data, bool exact);
};

Layer::Layer(int dendriteNum, int neuronNum)
{
	for (int i = 0;i < neuronNum;i++)
	{
		Neuron temporaryNeuron(dendriteNum);
		neurons.push_back(temporaryNeuron);
	}
}

vector<float> Layer::processData(vector<float>& data, bool exact)
{
	vector<float> newData;
	for (int i = 0;i < neurons.size();i++)
		newData.push_back(neurons[i].processInfo(data, exact));
	return newData;
}