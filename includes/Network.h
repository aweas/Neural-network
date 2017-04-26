#ifndef Network_H
#define Network_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Layer.h"
#define E 2.71828182845904523536

using namespace std;

class Network 
{
private:
    vector<Layer> layers;
    int inputSize;
    int outputSize;
    bool bias;

    double* multiplyLayers(vector<double> in1, double** in2, int lay1Neurons, int lay2Neurons);
    double* multiplyLayers(double* in1, double **in2, int lay1Neurons, int lay2Neurons);
    double activation(double value);
    double derivative(double value);

public:
    Network(int inputSize, int outputSize, bool bias);
    void importData(double* data);
    double* calculate(vector<double> input);
    void train(vector<vector<double>> input, vector<vector<double>> output, int times, int dataSize);
};

Network::Network(int iSize, int oSize, bool bis)
{
    inputSize = iSize;
    outputSize = oSize;
    bias = bis;

    Layer input(4, inputSize);
    layers.push_back(input);

    Layer output(outputSize, 4);
    layers.push_back(output);
}

double* Network::calculate(vector<double> input)
{
    double* answ = multiplyLayers(input, layers[0].toMatrix(), inputSize, layers[0].neuronNumber);
    layers[0].values = answ;
    // for(int i=1; i<layers.size();i++)
    // {
    //     answ = multiplyLayers(answ, layers[i].toMatrix(), layers[i-1].neuronNumber, layers[i].neuronNumber);    
    //     layers[i].values = answ;
    // }
    answ = multiplyLayers(answ, layers[1].toMatrix(), layers[0].neuronNumber, layers[1].neuronNumber);
    return answ;
}

double* Network::multiplyLayers(double* in1, double **in2, int lay1Neurons, int lay2Neurons)
{
    vector<double> temp;
    for(int i=0;i<lay1Neurons;i++)
        temp.push_back(in1[i]);
    return multiplyLayers(temp, in2, lay1Neurons, lay2Neurons);
}

double* Network::multiplyLayers(vector<double> in1, double **in2, int lay1Neurons, int lay2Neurons)
{
    //input is a horizontal array
    //[--1] (bias)
    //each layer will have to be a x*y array, x=neuron number, y=weights number + 1 (bias)
    //[----] w1
    //[----] w2
    //[----] b

    double* answer = new double[lay2Neurons];

    for(int i=0;i<lay2Neurons; i++)
    {
        double cell=0;

        for(int j=0; j<lay1Neurons; j++)
            cell+=in1[j]*in2[i][j];

        if(bias)
            cell+=in2[i][lay1Neurons];      //Include bias

        answer[i] = activation(cell);
    }
    return answer;
}

void Network::train(vector<vector<double>> input, vector<vector<double>> output, int times, int dataSize)
{
    double** l2calculated = new double*[dataSize];
    double** l2Error = new double*[dataSize];
    double** l2Delta = new double*[dataSize];
    double** l1calculated = new double*[dataSize];
    double** l1Error = new double*[dataSize];
    double** l1Delta = new double*[dataSize];

    for(int t=0; t<times; t++)
    {
        //Calculate our response
        for(int i=0;i<dataSize;i++)
        {
            l2calculated[i] = calculate(input[i]);
            l1calculated[i] = layers[0].values;
            l2Error[i] = new double[layers[1].neuronNumber];
            l2Delta[i] = new double[layers[1].neuronNumber];
            l1Error[i] = new double[layers[0].neuronNumber];
            l1Delta[i] = new double[layers[0].neuronNumber];
        }

        //Calculate error
        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[1].neuronNumber;j++)
                l2Error[i][j] = output[i][j] - l2calculated[i][j];

        //Weight error by derivative
        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[1].neuronNumber;j++)
                l2Delta[i][j] = l2Error[i][j]*derivative(l2calculated[i][j]);

        //Calculate hidden layer error
        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[0].neuronNumber;j++)
                for(int k=0; k<layers[1].neuronNumber; k++)
                    l1Error[i][j] = l2Delta[i][k]*layers[1].weights[k][j];
        
        //Weight it by derivative
        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[0].neuronNumber;j++)
                l1Delta[i][j] = l1Error[i][j]*derivative(l1calculated[i][j]);

        //Update weights
        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[1].neuronNumber;j++)
                for(int k=0;k<layers[1].weightsPerNeuron;k++)
                {
                    if(k==layers[0].neuronNumber)                    //Bias
                        layers[1].weights[j][k]+=l2Delta[i][j];
                    else
                        layers[1].weights[j][k]+=l2Delta[i][j]*l1calculated[i][k];
                }

        for(int i=0;i<dataSize;i++)
            for(int j=0;j<layers[0].neuronNumber;j++)
                for(int k=0;k<layers[0].weightsPerNeuron;k++)
                {
                    if(k==inputSize)                                //Bias
                        layers[0].weights[j][k]+=l1Delta[i][j];
                    else
                        layers[0].weights[j][k]+=l1Delta[i][j]*input[i][k];
                }
        
        if(t==times-1)
        {
            double err=0;
            for(int i=0;i<dataSize;i++)
                for(int j=0;j<layers[1].neuronNumber;j++)
                    err+=abs(l2Error[i][j]);
            err/=(layers[1].neuronNumber*dataSize);
            cout<<"Error: "<<err<<endl;
        }


        for(int i=0;i<dataSize;i++)
        {
            delete []l2Error[i];
            delete []l2Delta[i];
            delete []l1Error[i];
            delete []l1Delta[i];
            delete []l2calculated[i];
            delete []l1calculated[i];
        }
    }

    delete []l2Error;
    delete []l2Delta;
    delete []l1Error;
    delete []l1Delta;
    delete []l2calculated;
    delete []l1calculated;



}

double Network::activation(double value)
{
    double answ = 1/(1+pow(E, -value));
    return answ;
}

double Network::derivative(double value)
{
    double answ = pow(E, -value)/pow(1+pow(E,-value), 2);
    return answ;
}
#endif