#include <iostream>
#include "time.h"
#include <cstdlib>
#include <vector>

#include "includes/Network.h"

using namespace std;

int main()
{
    srand(1);
    vector<vector<double>> input;
    input.push_back({1,0});
    input.push_back({0,1});
    input.push_back({0,0});
    input.push_back({1,1});
    
    vector<vector<double>> output;
    output.push_back({1});
    output.push_back({1});
    output.push_back({0});
    output.push_back({0});

    Network mainNetwork(2, 1);

    mainNetwork.train(input, output, 60000, 4);
    double** out = new double*[4];

    for(int i=0;i<4;i++)
        out[i] = mainNetwork.calculate(input[i]);

    for(int i=0;i<4;i++)
        cout<<out[i][0]<<endl;
}