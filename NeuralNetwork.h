#pragma once
#include "Node.h"
#include <cmath>

class NeuralNetwork
{
	std::vector<std::vector<Node*>*> nodes;
	double fitness;
public:
	NeuralNetwork(std::vector<unsigned int> layersInfo, unsigned  int inputNumber);
	NeuralNetwork(const NeuralNetwork& original);
	NeuralNetwork(const NeuralNetwork& original, double mutationRate, double Deviation);

	std::vector< std::vector<double>> getOutput(std::vector<std::vector<double>> input); ///////////хглемхк гдеяэ
	void IncreaseFitness(double value);
	void ResetFitness();
	double getFitness();
	void calcFitness(std::vector< std::vector<double>> realOutputs, std::vector< std::vector<double>> idealOutput); ////////////днаюбхк щрн
	~NeuralNetwork();
};

