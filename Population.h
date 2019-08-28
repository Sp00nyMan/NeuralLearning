#pragma once
#include "NeuralNetwork.h"
class Population
{
	std::vector<NeuralNetwork*> population;
public:
	NeuralNetwork& operator [](int i);
	Population(std::vector<unsigned int> layersInfo,unsigned int inputNumber,unsigned int &popSize);
	void SortByFitness();
	int UpdatePopulation();
	void RunTest(std::vector<std::vector<double>> inputs, std::vector< std::vector<double>> idealOutput);
	~Population();
};

NeuralNetwork train(std::vector<std::vector<double>> inputs, std::vector< std::vector<double>> idealOutputs, std::vector<unsigned int> layersInfo, unsigned int& popSize);