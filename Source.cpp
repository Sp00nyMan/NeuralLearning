#include "Population.h"

int main()
{
	srand(time(NULL));
	unsigned int popSize = 100;
	std::vector<std::vector<double>> inputs = {
										{ 0, 1},
										{ 1, 0},
										{ 0, 0} };
	std::vector< std::vector<double>> idealOutputs = { 
													{1},
													{1}, 
													{0} };
	std::vector<unsigned int> layersInfo = { 3,5, idealOutputs[0].size() };
	
	NeuralNetwork trained = train(inputs, idealOutputs, layersInfo, popSize);

	std::vector< std::vector<double>> outs = trained.getOutput({ {1,1} });

	std::cout << outs[0][0];
	system("pause");
	return 0;
}