#ifndef Layer_H
#define Layer_H

#include <iostream>
#include <cstdlib>
#include "time.h"

using namespace std;

class Layer
{
private:
    double **weights;
    int neuronNumber;
    int weightsPerNeuron;
    void initLayer();

public:
    Layer(int neuronNumber, int weightsPerNeuron);
    void printLayer();
};

Layer::Layer(int nNumber, int wPerNeuron)
{
    neuronNumber=nNumber;
    weightsPerNeuron=(wPerNeuron+1);    //We have to include bias

    weights = new double*[nNumber];
    for(int i=0;i<nNumber;i++)
        weights[i] = new double[weightsPerNeuron];
    
    initLayer();
}

void Layer::printLayer()
{
    for(int i=0;i<neuronNumber;i++)
    {
        cout<<"Neuron "<<i<<": "<<endl;
        for(int j=0;j<weightsPerNeuron;j++)
            cout<<weights[i][j]<<endl;
    }
}

void Layer::initLayer()
{
    for(int i=0;i<neuronNumber;i++)
        for(int j=0;j<weightsPerNeuron;j++)
            weights[i][j]=rand()%1000/(double)1000;
}
#endif