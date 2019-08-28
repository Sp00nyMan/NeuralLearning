#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)( BYTE)(b))<<16)))
#define scale 0.7
#define MUTATION_RATE 0.02 //Чем меньше, тем выше вероятность мутации
#define DEVIATION 0.05 //Чем больше, тем больше будет отклонение от оригинала при мутации
#define MAXDEVIATION 0.001 //Минимально необходимая точность
#define MAXGENERATIONS 5000 //Максимальное количество поколений, которое будет обучаться сеть

class Node {
private:
	std::vector<double> weights;
	double correction;
	double output;

public:
	Node(int inputsNum = 0);
	Node(const Node& original, double maxDiviation); //Конструкутор копий - нужен для создания копии другого класса
	double Activate(std::vector<double> input); //Функция активации
	double getLastResult();
	int getWeightsNumber(); //Возвращает размер вектора weights
};