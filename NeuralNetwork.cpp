#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> layersInfo,unsigned int inputNumber) : fitness(0)
//Конструктор нейронной сети
//LayersInfo - хранит информацию о количестве слоёв и количеству нейронов в каждом слое
{
	Node* temp;
	std::vector<Node*>* buffer;
	for (int i = 0; i < layersInfo.size(); i++) //layersInfo.size() - это количество слоёв
	{
		buffer = new std::vector<Node*>; //Создаём вектор нейронов (слой)
		if (!buffer)
		{
			this->~NeuralNetwork();
			return;
		}
		nodes.push_back(buffer);
		for (int j = 0; j < layersInfo[i]; j++) //LayersInfo[i] хранит информацию о количестве нейронов в данном слое
		{
			temp = new Node(inputNumber); //Создаём нейрон, количество весов которого равно inputNumber
			if (!temp)
			{
				this->~NeuralNetwork();
				return;
			}
			nodes[i]->push_back(temp);
		}
		inputNumber = layersInfo[i]; //Количество весов в каждом нейроне следующего слоя будет равняться количеству нейронов в предыдущем слое
	}
}
NeuralNetwork::NeuralNetwork(const NeuralNetwork& original) : fitness(original.fitness)
//Конструктор копий
//Создаёт полную копию сети original
{
	Node* temp;
	std::vector<Node*>* buffer;
	for (int i = 0; i < original.nodes.size(); i++)
	{
		buffer = new std::vector<Node*>;
		if (!buffer)
		{
			this->~NeuralNetwork();
			return;
		}
		nodes.push_back(buffer);
		for (int j = 0; j < original.nodes[i]->size(); j++)
		{
			temp = new Node(*(original.nodes[i]->at(j)));
			if (!temp)
			{
				this->~NeuralNetwork();
				return;
			}
			nodes[i]->push_back(temp);
		}
	}
}
NeuralNetwork::NeuralNetwork(const NeuralNetwork& original, double mutationRate, double Deviation) : fitness(original.fitness)
//Конструктор копий
//Создаёт копию сети original с мутацией нейронов в ней
{
	Node* temp;
	int mutRate;
	if (mutationRate == 0)
	{
		mutRate = 0;
	}
	else
	{
		mutRate = (int)((1.0 / mutationRate) + 0.5);
	}
	std::vector<Node*>* buffer;
	if (!mutRate) //Если вероятность мутации равна нулю
	{				//тогда просто копируем исходную сеть
		for (int i = 0; i < original.nodes.size(); i++) 
		{
			buffer = new std::vector<Node*>;
			if (!buffer)
			{
				this->~NeuralNetwork();
				return;
			}
			nodes.push_back(buffer);
			for (int j = 0; j < original.nodes[i]->size(); j++)
			{
				temp = new Node(*(original.nodes[i]->at(j)));
				if (!temp)
				{
					this->~NeuralNetwork();
					return;
				}
				nodes[i]->push_back(temp);
			}
		}
	}
	else
	{
		for (int i = 0; i < original.nodes.size(); i++)
		{
			buffer = new std::vector<Node*>;
			if (!buffer)
			{
				this->~NeuralNetwork();
				return;
			}
			nodes.push_back(buffer);
			for (int j = 0; j < original.nodes[i]->size(); j++)
			{
				if (rand() % mutRate)//Если рандом решил, что мутации быть
					temp = new Node(*(original.nodes[i]->at(j)), Deviation);
					//if (rand() % 2)
					//	temp = new Node(*(original.nodes[i]->at(j)), Deviation); //Создаём нейрон с мутацией в положительную сторону
					//else
					//	temp = new Node(*(original.nodes[i]->at(j)), -Deviation); //Создаём нейрон с мутацией в отрицательную сторону
				else
					temp = new Node(*(original.nodes[i]->at(j))); //Просто создаём копию нейрона

				if (!temp)
				{
					this->~NeuralNetwork();
					return;
				}
				nodes[i]->push_back(temp);
			}
		}
	}
}
std::vector< std::vector<double>> NeuralNetwork::getOutput(std::vector<std::vector<double>> input)
{
	if (!nodes.size())
		return std::vector< std::vector<double>>();
	if (input[0].size() != nodes[0]->at(0)->getWeightsNumber())
		return std::vector< std::vector<double>>();
	std::vector< std::vector<double>> outs;
	std::vector<double> buffer;
	for (int k = 0; k < input.size(); k++)
	{
		for (int i = 0; i < nodes.size(); i++) //Цикл по слоям сети
		{
			buffer.clear();
			for (int j = 0; j < nodes[i]->size(); j++) //Цикл по нейронам слоя
			{
				buffer.push_back(nodes[i]->at(j)->Activate(input[k])); //В вектор outs записываем вывод нейрона 
			}
			input[k].clear();
			input[k] = buffer; //Выводы текущего слоя - это ввод следующего слоя
		}
		outs.push_back(buffer);
	}
	buffer.clear();
	return outs; //Возвращаем вывод последнего слоя
}
void NeuralNetwork::IncreaseFitness(double value)
{
	fitness += value;
}
void NeuralNetwork::ResetFitness()
{
	fitness = 0;
}
double NeuralNetwork::getFitness()
{
	return fitness;
}
void NeuralNetwork::calcFitness(std::vector< std::vector<double>> realOutputs, std::vector< std::vector<double>> idealOutput) //ДОБАВИЛ ЭТУ ФУНКЦИЮ
{
	ResetFitness();
	double flag;
	if (realOutputs.size() != idealOutput.size())
		return;
	for (int i = 0; i < realOutputs.size(); i++)
	{
		for (int j = 0; j < realOutputs[i].size(); j++)
		{
			//if (std::abs(realOutputs[i][0]) >= std::abs(realOutputs[i][1]))
			//	flag = 1;
			//else
			//	flag = 0;
			//if (flag != idealOutput[i][j])
				IncreaseFitness(std::abs(idealOutput[i][j] - realOutputs[i][j]));
		}
	}
}
NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i]->size(); j++)
		{
			delete nodes[i]->at(j);
		}
		delete nodes[i];
	}
	nodes.clear();
}