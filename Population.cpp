#include "Population.h"

NeuralNetwork& Population::operator[](int i)
{
	return *(population[i]);
}

Population::Population(std::vector<unsigned int> layersInfo, unsigned int inputNumber, unsigned int &popSize)
{
	NeuralNetwork* buffer;
	
	for (int i = 0; i < popSize; i++)
	{
		if (!i)
			buffer = new NeuralNetwork(layersInfo, inputNumber);
		else
			buffer = new NeuralNetwork(*population[0], 0.5, 1.0);
		if (!buffer)
		{
			popSize = i;
			return;
		}
		population.push_back(buffer);
	}
}

void Population::SortByFitness()
{
	std::sort(population.begin(), population.end(), [](NeuralNetwork * a, NeuralNetwork * b) {return a->getFitness() < b->getFitness(); });
}

int Population::UpdatePopulation()
{
	for (int i = 1; i < population.size(); i++) //Удаление всех особей в популяции, кроме лучшей (первой)
	{
		delete population[i];
	}
	NeuralNetwork* buffer;
	for (int i = 1; i < population.size(); i++) //Создаём новую популяцию на основе ген лучшей особи в предыдущей
	{
		buffer = new NeuralNetwork(*population[0], MUTATION_RATE, DEVIATION);
		if (!buffer)
		{
			population.resize(i);
			return i;
		}
		population[i] = buffer;
	}
	return population.size();
}

void Population::RunTest(std::vector<std::vector<double>> inputs, std::vector< std::vector<double>> idealOutput) //////////ИЗМЕНИЛ ЗДЕСЬ
{
	std::vector< std::vector<double>> outs;
	for (int i = 0; i < population.size(); i++)
	{
		outs.clear();
		outs = population[i]->getOutput(inputs);
		population[i]->calcFitness(outs, idealOutput);
	}
	SortByFitness();
}

Population::~Population()
{
	for (int i = 0; i < population.size(); i++)
	{
		delete population[i];
	}
	population.clear();
}


NeuralNetwork train(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> idealOutputs, std::vector<unsigned int> layersInfo, unsigned int& popSize)
{
	if (inputs.size() != idealOutputs.size())
	{
		std::cout << "INCORRECT INPUT/OUTPUT INFORMATION" << std::endl;
		system("pause");
	}

	////////График
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(0, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 0, 85, NULL);
	LineTo(hDC, 730, 85);
	////////

	Population pop(layersInfo, inputs[0].size(), popSize);
	int iterator = 0;
	while (iterator++ < MAXGENERATIONS)
	{
		pop.RunTest(inputs, idealOutputs);

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD position = { 0,10 }; //позиция x и y
	//SetConsoleCursorPosition(hConsole, position);

		////График
		MoveToEx(hDC, scale * iterator + 15, -scale * pop[0].getFitness() * 1000 + 85, NULL);
		LineTo(hDC, scale * iterator + 15, -scale * pop[0].getFitness() * 1000 + 85);

		//std::cout << "Best of generation " << iterator++ << " = " << pop[0].getFitness() << std::endl;

		if (abs(pop[0].getFitness()) < MAXDEVIATION)
			break;
		popSize = pop.UpdatePopulation();
	}

	//Вывод результатов обучения
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD position = { 0,10 }; //позиция x и y
	//SetConsoleCursorPosition(hConsole, position);
	//for (int i = 0; i < 30; i++)
	//	std::cout << "=";
	//std::cout << std::endl;
	//if (pop[0].getFitness() < MAXDEVIATION)
	//{
	//	std::vector< std::vector<double>> output = pop[0].getOutput(inputs);
	//	std::cout << "Solution found on " << iterator - 1 << " generation" << std::endl;
	//	std::cout << "Solution is: " << std::endl;
	//	for (int i = 0; i < inputs.size(); i++)
	//		std::cout << output[i][0] << std::endl;
	//}
	//else
	//{
	//	std::cout << "Solution wasn't found " << std::endl;
	//	std::vector< std::vector<double>> output = pop[0].getOutput(inputs);
	//	std::cout << "The best is:" << std::endl;
	//	for (int i = 0; i < output.size(); i++)
	//		std::cout << output[i][0] << std::endl;
	//}

	return pop[0];
}