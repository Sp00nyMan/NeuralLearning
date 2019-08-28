#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> layersInfo,unsigned int inputNumber) : fitness(0)
//����������� ��������� ����
//LayersInfo - ������ ���������� � ���������� ���� � ���������� �������� � ������ ����
{
	Node* temp;
	std::vector<Node*>* buffer;
	for (int i = 0; i < layersInfo.size(); i++) //layersInfo.size() - ��� ���������� ����
	{
		buffer = new std::vector<Node*>; //������ ������ �������� (����)
		if (!buffer)
		{
			this->~NeuralNetwork();
			return;
		}
		nodes.push_back(buffer);
		for (int j = 0; j < layersInfo[i]; j++) //LayersInfo[i] ������ ���������� � ���������� �������� � ������ ����
		{
			temp = new Node(inputNumber); //������ ������, ���������� ����� �������� ����� inputNumber
			if (!temp)
			{
				this->~NeuralNetwork();
				return;
			}
			nodes[i]->push_back(temp);
		}
		inputNumber = layersInfo[i]; //���������� ����� � ������ ������� ���������� ���� ����� ��������� ���������� �������� � ���������� ����
	}
}
NeuralNetwork::NeuralNetwork(const NeuralNetwork& original) : fitness(original.fitness)
//����������� �����
//������ ������ ����� ���� original
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
//����������� �����
//������ ����� ���� original � �������� �������� � ���
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
	if (!mutRate) //���� ����������� ������� ����� ����
	{				//����� ������ �������� �������� ����
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
				if (rand() % mutRate)//���� ������ �����, ��� ������� ����
					temp = new Node(*(original.nodes[i]->at(j)), Deviation);
					//if (rand() % 2)
					//	temp = new Node(*(original.nodes[i]->at(j)), Deviation); //������ ������ � �������� � ������������� �������
					//else
					//	temp = new Node(*(original.nodes[i]->at(j)), -Deviation); //������ ������ � �������� � ������������� �������
				else
					temp = new Node(*(original.nodes[i]->at(j))); //������ ������ ����� �������

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
		for (int i = 0; i < nodes.size(); i++) //���� �� ����� ����
		{
			buffer.clear();
			for (int j = 0; j < nodes[i]->size(); j++) //���� �� �������� ����
			{
				buffer.push_back(nodes[i]->at(j)->Activate(input[k])); //� ������ outs ���������� ����� ������� 
			}
			input[k].clear();
			input[k] = buffer; //������ �������� ���� - ��� ���� ���������� ����
		}
		outs.push_back(buffer);
	}
	buffer.clear();
	return outs; //���������� ����� ���������� ����
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
void NeuralNetwork::calcFitness(std::vector< std::vector<double>> realOutputs, std::vector< std::vector<double>> idealOutput) //������� ��� �������
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