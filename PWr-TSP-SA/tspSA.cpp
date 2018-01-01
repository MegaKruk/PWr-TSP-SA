#include "Stopwatch.h"
#include "tspSA.h"

void tspSA::pathInit(std::vector<int> &calcPath, int noOfCities)
{
	calcPath.clear();
	calcPath.resize(noOfCities + 1);
	for (int i = 0; i < noOfCities; i++)
	{
		calcPath[i] = i;
		if (i == noOfCities - 1)
			calcPath[i + 1] = calcPath[0];
	}
}

int tspSA::calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities)
{
	int tmpCost = 0;
	for (int i = 0; i < noOfCities; i++)
	{
		//std::cout << endl << seq[i] << endl;
		int a = calcPath[i];
		//std::cout << endl << "a= "<< a;
		int b = calcPath[i + 1];
		//std::cout << endl << "b= " << b;
		tmpCost += adjacancyMatrix[a][b % (noOfCities)];

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
int tspSA::TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities)
{
	srand(time(0));

	// s - initial candidate
	int currCost = calculateCost(adjacancyMatrix, calcPath, noOfCities);

	// best = s
	int bestCost = currCost;

	std::vector<int> bestPath;
	bestPath.clear();
	bestPath.resize(noOfCities + 1);

	for (int i = 0; i < noOfCities + 1; i++)
	{
		bestPath[i] = calcPath[i];
	}

	// glowna petla
	for (double T = 1; T >= 1E-4; T *= 0.9)
		for (int n = 0; n <= 100 * noOfCities; n++)
		{

			int i = randInt(1, noOfCities - 1);
			int j = randInt(1, noOfCities - 1);
			std::swap(calcPath[i], calcPath[j]);

			// r - tweak attempt
			int newCost = calculateCost(adjacancyMatrix, calcPath, noOfCities);

			if (newCost < currCost || randFraction() < exp((currCost - newCost) / T))
			{
				// s = r
				currCost = newCost;

				// best = s
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

	std::cout << endl << endl << "Cost:\t" << bestCost << endl;
	std::cout << "Path:\t";
	for (int i = 0; i < noOfCities + 1; i++)
	{
		cout << bestPath[i] << "\t";
	}
	bestPath.clear();
	return bestCost;
}

// wczytanie danych, przygotowanie funkcji TSP
void tspSA::tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &calcPath, int noOfCities)
{
	string filename, filePointer;
	ifstream myFile;
	std::cout << "Enter filename. Must be in 'data' folder: \n";
	std::cin >> filename;
	myFile.open("data/" + filename);
	if (myFile.is_open())
	{
		do myFile >> filePointer;
		while (filePointer != "DIMENSION:");

		myFile >> filePointer;
		noOfCities = atoi(filePointer.c_str());

		adjacancyMatrix.resize(noOfCities);
		for (int i = 0; i < noOfCities; ++i)
			adjacancyMatrix[i].resize(noOfCities);

		calcPath.resize(noOfCities + 1);

		do myFile >> filePointer;
		while (filePointer != "EDGE_WEIGHT_TYPE:");
		myFile >> filePointer;


		if (filePointer == "EXPLICIT")
		{
			do myFile >> filePointer;
			while (filePointer != "EDGE_WEIGHT_FORMAT:");
			myFile >> filePointer;

			if (filePointer == "FULL_MATRIX")
			{
				do myFile >> filePointer;
				while (filePointer != "EDGE_WEIGHT_SECTION");

				for (int i = 0; i < noOfCities; i++)
				{
					std::cout << "\n";
					for (int j = 0; j < noOfCities; j++)
					{
						myFile >> adjacancyMatrix[i][j];
						std::cout << adjacancyMatrix[i][j] << "\t";
					}
				}
			}
			else
				std::cout << "\nError! Unsupported format.";
		}
		else if (filePointer == "EUC_2D")
		{
			std::vector<double> xVect;
			xVect.clear();
			std::vector<double> yVect;
			yVect.clear();

			do myFile >> filePointer;
			while (filePointer != "NODE_COORD_SECTION");

			for (int i = 0; i < noOfCities; i++)
			{
				myFile >> filePointer;

				myFile >> filePointer;
				xVect.push_back(atof(filePointer.c_str()));

				myFile >> filePointer;
				yVect.push_back(atof(filePointer.c_str()));

				std::cout << "\n";
				std::cout << (i + 1) << "\t" << xVect[i] << "\t" << yVect[i] << endl;
			}
			std::cout << endl;

			for (int i = 0; i < noOfCities; i++)
			{
				for (int j = 0; j < noOfCities; j++)
				{
					if (i != j)
					{
						double xDiff = xVect.at(i) - xVect.at(j);
						double yDiff = yVect.at(i) - yVect.at(j);
						int cost = std::nearbyint(sqrt(xDiff * xDiff + yDiff * yDiff));
						adjacancyMatrix[i][j] = cost;
						//std::cout << adjacancyMatrix[i][j] << "\t";
					}
					if (i == j)
					{
						adjacancyMatrix[i][j] = 0;
						//std::cout << adjacancyMatrix[i][j] << "\t";
					}
				}
			}
		}
		else
			std::cout << "\nError! Unsupported format.";
		myFile.close();

		// main menu
		int option;
		std::cout << endl;
		std::cout << "\n1 - Test algorithm\n2 - Make measurements\n";
		std::cin >> option;
		
		switch (option)
		{
		case 1:
		{
			Stopwatch *timer = new Stopwatch();
			timer->point1 = chrono::high_resolution_clock::now();
			pathInit(calcPath, noOfCities);
			TSP(adjacancyMatrix, calcPath, noOfCities);
			std::cout << endl << timer->countTimeDiff() << " nanosecs to complete this action\n";
			calcPath.clear();
			adjacancyMatrix.clear();
			break;

		}
		case 2:
		{
			ofstream myOutput("output.txt");
			int result = 0;
			Stopwatch *timer = new Stopwatch();

			for (int i = 0; i < 51; i++)
			{
				timer->point1 = chrono::high_resolution_clock::now();
				pathInit(calcPath, noOfCities);
				result = TSP(adjacancyMatrix, calcPath, noOfCities);
				myOutput << timer->countTimeDiff() << "\t" << result << endl;
				calcPath.clear();
				std::cout << endl << (i + 1) * 100 / 51 << " % done";
			}
			adjacancyMatrix.clear();
			break;
		}
		default:
		{
			std::cout << "Wrong input";
			break;
		}
		}
	}
	else
		std::cout << "Error! No such file in 'data' directory";
}

// gettery
std::vector<std::vector<int>> tspSA::getAdjacancyMatrix(void)
{
	return std::vector<std::vector<int>>(adjacancyMatrix);
}

std::vector<int> tspSA::getCalcPath(void)
{
	return std::vector<int>(calcPath);
}

int tspSA::getNoOfCities(void)
{
	return noOfCities;
}

// funkcja inicjuj¹ca obiekt
void tspSA::start(void)
{
	tspInit(getAdjacancyMatrix(), getCalcPath(), getNoOfCities());
}

tspSA::tspSA()
{

}

tspSA::~tspSA()
{

}
