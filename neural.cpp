#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

#define E 2.71828182845904523536

using namespace std;

double activation(double value);
double derivative(double value);
double multiplyVectors(double* vec1, double* vec2, int size);
void printVector(double* vec, int size);
void substractVectors(double* vec1, double* vec2, double* output, int size);
void calculateAnswer(double* input);

double weights1[4][2];
double weights2[4];

int main()
{
    srand(1);

    double input[4][2] = {{0,0},
                       {0,1},
                       {1,1},
                       {1,0}};

    double output[4] = {0,
                     1,
                     0,
                     1};
    
    //Weights for 4 neurons with 2 inputs
    
    //One neuron with 4 inputs
    

    // Initialize weights with random values
    for(int i=0;i<4;i++)
    {
        weights2[i]=(rand()%1000)/(double)1000;
        for(int j=0;j<2;j++)
            weights1[i][j]=(rand()%1000)/(double)1000;;
    }

    // cout<<"Starting weights: "<<endl;
    // for(int i=0;i<4;i++)
    //     printVector(weights1[i],2);
    // cout<<endl;
    // printVector(weights2, 4);

    //60000 training cycles
    for(int k=0;k<100000;k++)
    {
        double l1[4][4];    //4 data sets:4 neurons
        double l2[4];       //4 data sets:1 neuron
        double l2_err[4];
        double l2_delta[4];
        double l1_err[4][4];
        double l1_delta[4][4];

        //Calculate responce
        for(int i=0;i<4;i++)    //data cycles
            for(int j=0;j<4;j++)    //neuron cycles
                l1[i][j]=activation(multiplyVectors(input[i],weights1[j], 2));

        for(int i=0;i<4;i++)
            l2[i]=activation(multiplyVectors(l1[i], weights2, 4));

        //Output layer error calculating
        substractVectors(output, l2, l2_err, 4);

        //Backwards propagation
        //Each neuron calculates its error for 4 iterations (important: NEURON, not its weights)
        for(int i=0;i<4;i++)
            l2_delta[i] = l2_err[i]*derivative(l2[i]);
        
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                l1_err[i][j] = weights2[j]*l2_delta[i];
        
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                l1_delta[i][j] = l1_err[i][j]*derivative(l1[i][j]);
        
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                weights2[j]+=l2_delta[i]*l1[i][j];
        
         for(int i=0;i<4;i++)
            for(int l=0;l<4;l++)
                for(int j=0;j<2;j++)
                    weights1[l][j]+=l1_delta[i][l]*input[i][j];
    }

    //Print results
    // for(double i=0;i<1;i+=0.001)
    //     for(double j=0;j<1;j+=0.001)
    //     {
    //         double input2[2]={i,j};
    //         calculateAnswer(input2);
    //     }


    cout<<"End weights: "<<endl;
    for(int i=0;i<4;i++)
        printVector(weights1[i],2);
    cout<<endl;
    printVector(weights2, 4);

    for(int i=0;i<4;i++)
        calculateAnswer(input[i]);
}

double activation(double value)
{
    double answ = 1/(1+pow(E, -value));
    return answ;
}

double derivative(double value)
{
    double answ = pow(E, -value)/pow(1+pow(E,-value), 2);
    return answ;
}

double multiplyVectors(double* vec1, double* vec2, int size)
{
    double answ=0;
    for(int i=0;i<size;i++)
    {
        double addition = vec1[i]*vec2[i];
        answ+= addition;
    }
    return answ;
}

void printVector(double* vec, int size)
{
    for(int i=0;i<size;i++)
        cout<<vec[i]<<endl;
    cout<<endl;
}

void substractVectors(double* vec1, double* vec2, double* output, int size)
{
    for(int i=0; i<size; i++)
        output[i]=vec1[i]-vec2[i];
}

void calculateAnswer(double* input)
{
    double l1[4];    //4 neurons:4 data
    double l2;       //1 neuron:4 data

    for(int i=0;i<4;i++)    //neuron cycles
        l1[i]=activation(multiplyVectors(input,weights1[i], 2));

    l2=activation(multiplyVectors(l1, weights2, 4));

    cout<<input[0]<<"\t"<<input[1]<<"\t"<<l2<<endl;
}