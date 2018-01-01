#pragma once
#include<stdlib.h>
#include<string>
#include<limits.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>

class tspSA
{
private:
	std::vector<std::vector<int>> adjacancyMatrix;
	std::vector<int> calcPath;
	int noOfCities;

public:
	tspSA();
	~tspSA();
	void pathInit(std::vector<int> &calcPath, int noOfCities);
	int calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities);
	int randInt(int l, int r);
	double randFraction(void);
	int TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities);
	void tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities);
	std::vector<std::vector<int>> getAdjacancyMatrix(void);
	std::vector<int> getCalcPath(void);
	void start(void);
	int getNoOfCities(void);
};