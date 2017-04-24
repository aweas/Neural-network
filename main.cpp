#include <iostream>
#include "time.h"
#include <cstdlib>

#include "includes/Network.h"

using namespace std;

int main()
{
    srand(0);
    double input[2] = {1,0};

    Network mainNetwork(2, 1);
    double *output = mainNetwork.calculate(input);

    cout<<output[0]<<endl;
}