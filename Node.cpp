#include "Node.h"

Node::Node(int inputsNum)
	: weights(inputsNum), correction(0), output(0)
{
}

Node::Node(const Node& original, double maxDiviation) : output(0)
//Создаём копию нейрона original, но с мутатацией его весов в пределах maxDeviation
{
	double buf;
	for (int i = 0; i < original.weights.size(); i++)
	{
		buf = (rand() % (int)(maxDiviation * 100 + 0.5)) / 100.0;
		if (rand() % 2)
			buf = -buf;
		weights.push_back(original.weights[i] + buf); 
	}
	buf = (rand() % (int)(maxDiviation * 100 + 0.5)) / 100.0;
	if (rand() % 2)
		buf = -buf;
	correction = original.correction + buf;
}

double Node::Activate(std::vector<double> input) 
//Функция активации (Можно добавить сигмоид или другую функцию)
{
	output = 0;
	if (input.size() != weights.size())
		return 0;

	for (int i = 0; i < input.size(); i++)
	{
		output += weights[i] * input[i];
	}
	output += correction;
	return output;
}

double Node::getLastResult()
{
	return output;
}

int Node::getWeightsNumber()
{
	return weights.size();
}