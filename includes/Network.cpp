#include <iostream>
#include <vector>
#include "Layer.h"

using namespace std;

class Network 
{
    private:
    vector<Layer> layers;

    public:
    Network(int inputSize);
};

using namespace std;

Network::Network(int inputSize)
{
    Layer input = new Layer(4, inputSize);
    layers.push_back();

    layers[0].printLayer();
}