#pragma once

#include "Layer.h"

#include <iostream>

class Network
{
private:
	Layer *hidden;
	Layer *output;
public:
	Network(int inputSources, int neuronsPerLayer, int outputNeurons);
	void processData(vector<float>& data);
};

Network::Network(int inputSources, int neuronsPerLayer, int outputNumber)
{
	hidden = new Layer(inputSources, neuronsPerLayer);
	output = new Layer(neuronsPerLayer, outputNumber);
}

void Network::processData(vector<float>& data)
{
	vector<float> temp;
	vector<float> tempExact;

	temp = output->processData(hidden->processData(data, false), false);
	tempExact = output->processData(hidden->processData(data, false), true);

	for (int i = 0;i < temp.size();i++)
		cout << temp[i] << " ("<<tempExact[i]<<")"<<endl;
}