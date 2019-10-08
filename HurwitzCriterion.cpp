#include <iostream>
#include <vector>

using namespace std;

void enterIndArr(int aIndAmount, vector <double>& indexArr);
void createIndMatrix(int aIndAmount, vector <double>& indexArr ,vector <vector <double>>& hurwitzMatrix);
double detCalc(int aIndAmount, vector <vector <double>>& hurwitzMatrix);
void getMatrix(int aIndAmount, vector <vector <double>>& hurwitzMatrix, vector <vector <double>>& tempMatrix, int i, int j);

int main()
{
	int aIndAmount = 0;
	double det = 1;

	cout << "The matrix should look like:" << endl;
	cout << "3 7 0" << endl << "1 5 0" << endl << "0 3 7" << endl;

	cout << ">> Enter the number of monomials: " << endl;
	cin >> aIndAmount;

	vector <double> indexArr(aIndAmount);
	vector <vector <double>> hurwitzMatrix(aIndAmount - 1, vector <double>(aIndAmount - 1));

	enterIndArr(aIndAmount, indexArr);
	createIndMatrix(aIndAmount, indexArr, hurwitzMatrix);

	for (int i = 0; i < aIndAmount - 1; i++)
	{
		vector <vector <double>> tempHurwitzMatrix(i, vector <double>(i));
		tempHurwitzMatrix = hurwitzMatrix;
		if (det > 0)
		{
			det = detCalc(i + 2, tempHurwitzMatrix);
		}
		else
		{
			cout << "System is unstable!" << endl;
			return 0;
		}
	}
	cout << "System is stable!" << endl;
	return 0;
}

void enterIndArr(int aIndAmount, vector <double>& indexArr)
{
	cout << ">> Enter the coefficients of the characteristic equation: " << endl;

	for (int i = 0; i < aIndAmount; i++)
	{
		cin >> indexArr[i];
	}
}

void createIndMatrix(int aIndAmount, vector <double>& indexArr, vector <vector <double>>& hurwitzMatrix)
{
	for (int i = 0; i < aIndAmount - 1; i++)
	{
		for (int j = 0; j < aIndAmount - 1; j++)
		{
			if (i == j)
			{
				hurwitzMatrix[i][j] = indexArr[i];
			}
		}
		// Нужна математика для остальных элементов :(
	}
}

double detCalc(int aIndAmount, vector <vector <double>>& hurwitzMatrix)
{
	double det = 0;
	int coef = 1;
	vector <vector <double>> tempMatrix = hurwitzMatrix;

	if (aIndAmount - 1 == 1)
	{
		det = tempMatrix[0][0];
	}
	else if (aIndAmount - 1 == 2)
	{
		det = tempMatrix[0][0] * tempMatrix[1][1] - tempMatrix[1][0] * tempMatrix[0][1];
	}
	else if (aIndAmount - 1 < 0)
	{
		cout << "Unable to calculate ф matrix less than zero!" << endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < aIndAmount - 1; i++)
		{
			getMatrix(aIndAmount - 1, hurwitzMatrix, tempMatrix, i, 0);
			det = det + coef * hurwitzMatrix[i][0] * detCalc(aIndAmount - 1, tempMatrix);
		}
	}
	return det;
}

void getMatrix(int aIndAmount, vector <vector <double>>& hurwitzMatrix, vector <vector <double>>& tempMatrix, int i, int j)
{
	int di = 0;
	int dj = 0;

	for (int ki = 0; ki < aIndAmount - 1; ki++)
	{
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (int kj = 0; kj < aIndAmount - 1; kj++)
		{
			if (kj == j)
			{
				dj = 1;
			}
			tempMatrix[ki][kj] = hurwitzMatrix[ki + di][kj + dj];
		}
	}
}