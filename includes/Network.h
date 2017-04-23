#ifndef Network_H
#define Network_H

#include <iostream>
#include <vector>
#include "Layer.h"

using namespace std;

class Network 
{
private:
    vector<Layer> layers;
    void multiplyMatrix(int* in1, int** in2, int* output);

public:
    Network(int inputSize, int outputSize);
    void calculate(int* input, int* output);
};

Network::Network(int inputSize, int outputSize)
{
    Layer input(4, inputSize);
    layers.push_back(input);

    layers[0].printLayer();

    Layer output(outputSize, 4);
    layers.push_back(output);
    cout<<endl;
    layers[1].printLayer();
}

void Network::calculate(int* input, int* output)
{
    //input is a horizontal array
    //[--1] (bias)
    //each layer will have to be a x*y array, x=neuron number, y=weights number + 1 (bias)
    //[----]
    //[----]
    //[----]

    
}
#endif