#include <iostream>
#include <conio.h>
using namespace std;
#define m 3
#define n 3
float matrix[m][n] = {{0, 2, 3}, {4, 5, 6}, {7, 8, 9}};

void display();
void exchange_row(int, int);				 // R1<->R2, exchange two rows
void divide_row(int, float);				 // R=R/c, divide a row with a constant
void multiply_subtract_row(int, int, float); // R1=R1-c*R2, multiply R2 with c and subtract from R1

int main()
{
	if (m < n)
		int d = m;
	else
		int d = n;
	display();

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				float pivot = matrix[i][j];
				if (pivot == 0)
				{
					for (int h = i + 1; h < m; h++)
					{
						pivot = matrix[h][j];
						if (pivot != 0)
						{
							exchange_row(i, h);
							break;
						}
					}
				}
				if (pivot != 0)
				{
					divide_row(i, pivot);

					// pivot ko mathi ka lai 0 banauni
					if (i - 1 >= 0)
					{
						for (int h = i - 1; h >= 0; h--)
						{
							float c = matrix[h][j];
							multiply_subtract_row(h, i, c);
						}
					}

					// pivot ko tala ko row haru ko operation
					for (int h = i + 1; h < m; h++)
					{
						float c = matrix[h][j];
						multiply_subtract_row(h, i, c);
					}
				}
			}
		}
	}
	getch();
	return 0;
}

void display()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

void exchange_row(int r1, int r2)
{
	float temp;
	cout << "R" << r1 + 1 << "<=>R" << r2 + 1 << endl;
	for (int w = 0; w < n; w++)
	{
		temp = matrix[r1][w];
		matrix[r1][w] = matrix[r2][w];
		matrix[r2][w] = temp;
	}
	display();
}

void divide_row(int r, float c)
{
	if (c != 1)
	{
		cout << "R" << r + 1 << "=>R" << r + 1 << "/" << c << endl;
		for (int w = 0; w < n; w++)
		{
			matrix[r][w] = matrix[r][w] / c;
			if (matrix[r][w] == 0)
				matrix[r][w] = 0;
		}
		display();
	}
}

void multiply_subtract_row(int r1, int r2, float c)
{
	if (c != 0)
	{
		cout << "R" << r1 + 1 << "=>R" << r1 + 1 << "-(" << c << ")*R" << r2 + 1 << endl;
		for (int w = 0; w < n; w++)
		{
			matrix[r1][w] = matrix[r1][w] - c * matrix[r2][w];
			if (matrix[r1][w] == 0)
				matrix[r1][w] = 0;
		}
		display();
	}
}
