#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)( BYTE)(b))<<16)))
#define scale 0.7
#define MUTATION_RATE 0.02 //��� ������, ��� ���� ����������� �������
#define DEVIATION 0.05 //��� ������, ��� ������ ����� ���������� �� ��������� ��� �������
#define MAXDEVIATION 0.001 //���������� ����������� ��������
#define MAXGENERATIONS 5000 //������������ ���������� ���������, ������� ����� ��������� ����

class Node {
private:
	std::vector<double> weights;
	double correction;
	double output;

public:
	Node(int inputsNum = 0);
	Node(const Node& original, double maxDiviation); //������������ ����� - ����� ��� �������� ����� ������� ������
	double Activate(std::vector<double> input); //������� ���������
	double getLastResult();
	int getWeightsNumber(); //���������� ������ ������� weights
};