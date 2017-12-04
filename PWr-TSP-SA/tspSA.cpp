#include "Stopwatch.h"
#include "tspSA.h"

void tspSA::loadFromFile(int adjacancyMatrix[noOfCities][noOfCities])
{
	ifstream myFile("gr17_d.txt");
	for (int i = 0; i < noOfCities; i++)
	{
		cout << "\n";
		for (int j = 0; j < noOfCities; j++)
		{
			myFile >> adjacancyMatrix[i][j];
			cout << adjacancyMatrix[i][j] << "\t";
		}
	}
}

void tspSA::pathInit(int calcPath[noOfCities+1])
{
	for (int i = 0; i < noOfCities; i++)
	{
		calcPath[i] = i;
		if (i == noOfCities - 1)
			calcPath[i + 1] = calcPath[0];
	}
}

int tspSA::calculateCost(int adjacancyMatrix[noOfCities][noOfCities], int calcPath[noOfCities+1])
{
	int tmpCost = 0;
	for (int i = 0; i < noOfCities; i++)
	{
		//cout << endl << seq[i] << endl;
		
		int a = calcPath[i];
		//cout << endl << "a= "<< a;
		int b = calcPath[i + 1];
		//cout << endl << "b= " << b;
		tmpCost += adjacancyMatrix[a][b % (noOfCities)];
		/*if (i == noOfCities - 1)
		{
			calcPath[i + 1] = calcPath[0];
			tmpCost += adjacancyMatrix[calcPath[i]][calcPath[0]];
		}*/
	}
	return tmpCost;
}

int tspSA::randInt(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

double tspSA::randFraction(void)
{
	return randInt(1, 10000) / 10000;
}

// g³owna funkcja programu
int tspSA::TSP(int adjacancyMatrix[noOfCities][noOfCities], int calcPath[noOfCities+1])
{
	srand(time(0));

	// s - initial candidate
	int currCost = calculateCost(adjacancyMatrix, calcPath);

	// best = s
	int bestCost = currCost;
	int bestPath[noOfCities + 1];
	for (int i = 0; i < noOfCities + 1; i++)
	{
		bestPath[i] = calcPath[i];
	}

	// glowna petla
	for (double T = 1E128; T >= 1E-4; T *= 0.9)
		for (int n = 0; n <= 100 * noOfCities; n++)
		{
			
			int i = randInt(1, noOfCities-1);
			int j = randInt(1, noOfCities-1);
			std::swap(calcPath[i], calcPath[j]);

			// r - tweak attempt
			int newCost = calculateCost(adjacancyMatrix, calcPath);

			if (newCost < currCost || randFraction() < exp((currCost - newCost) / T))
			{
				// s = r
				currCost = newCost; 

				// best = s
				//bestCost = std::min(bestCost, currCost);
				if (currCost < bestCost)
				{
					bestCost = currCost;
					for (int i = 0; i < noOfCities + 1; i++)
					{
						bestPath[i] = calcPath[i];
					}
				}
			}
			else
				std::swap(calcPath[i], calcPath[j]);

		}

	cout << endl << endl << "Cost:\t" << bestCost << endl;
	cout << "Path:\t";
	for (int i = 0; i < noOfCities + 1; i++)
	{
		cout << bestPath[i] << "\t";
	}
	return bestCost;
}

// testowanie jednej instancji algorytmu dla danych z gr17_d.txt w folderze z kodem
void tspSA::testAlgorithm(void)
{
	int adjacencyMatrix[noOfCities][noOfCities];
	int calcPath[noOfCities + 1];

	loadFromFile(adjacencyMatrix);
	pathInit(calcPath);

	Stopwatch *timer = new Stopwatch();
	timer->point1 = chrono::high_resolution_clock::now();
	TSP(adjacencyMatrix, calcPath);
	cout << endl << timer->countTimeDiff() << " nanosecs to complete this action\n";
	//cout << "Link: https://people.sc.fsu.edu/~jburkardt/datasets/tsp/tsp.html";
	//cout << "\nGR17 is a set of 17 cities, from TSPLIB.\nThe minimal tour has length 2085.\n\n";
	//cout << "Calculated minimal cost: " << bestCost << endl;
	//cout << "Path:\t";
	//for (int i = 0; i <= noOfCities; i++)
		//cout << calcPath[i] << "\t";
}

// 100 pomiarów czasu oraz eksport pomiarów do pliku output.txt
void tspSA::makeMeasurements(void)
{
	int adjacencyMatrix[noOfCities][noOfCities];
	int calcPath[noOfCities + 1];

	loadFromFile(adjacencyMatrix);
	pathInit(calcPath);

	Stopwatch *timer = new Stopwatch();
	ofstream myOutput("output.txt");
	int result = 0;

	for (int i = 0; i < 51; i++)
	{
		timer->point1 = chrono::high_resolution_clock::now();
		result = TSP(adjacencyMatrix, calcPath);
		myOutput << timer->countTimeDiff() << "\t" << result << endl;
	}
	cout << "\nDone";
}

tspSA::tspSA()
{

}

tspSA::~tspSA()
{

}
