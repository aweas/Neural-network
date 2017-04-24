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
    double* multiplyLayers(double* in1, double** in2, int lay1Neurons, int lay2Neurons);

public:
    Network(int inputSize, int outputSize);
    double* calculate(double* input);
};

Network::Network(int inputSize, int outputSize)
{
    Layer input(4, inputSize);
    layers.push_back(input);

    Layer output(outputSize, 4);
    layers.push_back(output);
}

double* Network::calculate(double* input)
{
    //input is a horizontal array
    //[--1] (bias)
    //each layer will have to be a x*y array, x=neuron number, y=weights number + 1 (bias)
    //[----] w1
    //[----] w2
    //[----] b

    double *answ = multiplyLayers(input, layers[0].toMatrix(), 2, 4);

    for(int i=1;i<layers.size();i++)
        answ = multiplyLayers(answ, layers[1].toMatrix(), 4, 1);    

    return answ;
}

double* Network::multiplyLayers(double *in1, double **in2, int lay1Neurons, int lay2Neurons)
{
    double* answer = new double[lay1Neurons];

    for(int i=0;i<lay2Neurons; i++)
    {
        double cell=0;

        for(int j=0; j<lay1Neurons; j++)
            cell+=in1[j]*in2[i][j];

        cell+=in2[i][lay1Neurons];      //Including bias
        answer[i] = cell;
    }
    return answer;
}
#endif