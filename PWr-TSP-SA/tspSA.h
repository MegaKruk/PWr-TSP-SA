#pragma once
#include<stdlib.h>
#include<string>
#include<limits.h>
#include<iostream>
#include<fstream>
#include<algorithm>

class tspSA
{
private:
	static const int noOfCities = 17;

public:
	int adjacencyMatrix[noOfCities][noOfCities];
	int calcPath[noOfCities + 1];
	//int bestPath[noOfCities + 1];

public:
	tspSA();
	~tspSA();
	void loadFromFile(int adjacancyMatrix[noOfCities][noOfCities]);
	void pathInit(int calcPath[noOfCities]);
	int calculateCost(int adjacancyMatrix[noOfCities][noOfCities], int calcPath[noOfCities]);
	int randInt(int l, int r);
	double randFraction(void);
	int TSP(int adjacancyMatrix[noOfCities][noOfCities], int calcPath[noOfCities]);
	//int getBestCost(void);
	void testAlgorithm(void);
	void makeMeasurements(void);

};