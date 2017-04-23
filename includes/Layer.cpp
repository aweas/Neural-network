#include <iostream>
#include "Layer.h"

using namespace std;

Layer::Layer(int nNumber, int wPerNeuron)
{
    neuronNumber=nNumber;
    weightsPerNeuron=wPerNeuron;

    weights = new int*[nNumber];
    for(int i=0;i<nNumber;i++)
        weights[i] = new int[wPerNeuron];
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