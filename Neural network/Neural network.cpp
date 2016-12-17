// Neural network.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include <vector>

#include "neuron.h"
#include "Network.h"

using namespace std;

int main()
{
	srand(time(NULL));
	int inputNumber = 2;
	vector<float> data;

	cout << "Data given: ";
	for (int i = 0;i < inputNumber;i++)
	{
		data.push_back(rand() % 2);
		cout << data[i] << " ";
	}
	cout << endl;
	
	Network brain(2, 2, 1);

	brain.processData(data);
	cin.get();
    return 0;
}

