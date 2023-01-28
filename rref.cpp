#include <iostream>
#include<conio.h>
using namespace std;
#define m 3
#define n 3
float matrix[m][n] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

void display();

int main()
{
	display();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				float pivot = matrix[i][j];
				if (pivot != 0)
				{
					// r1 = r1/pivot
					cout << "R" << i + 1 << "->R" << i + 1 << "/" << pivot << endl;
					for (int w = j; w < n; w++)
					{
						matrix[i][w] = matrix[i][w] / pivot; // divide r1 by pivot
					}
					display();

					// pivot ko mathi ka lai 0 banauni
					if (i - 1 >= 0)
					{
						for (int h = i - 1; h >= 0; h--)
						{
							float c1 = matrix[h][j];
							cout << "R" << h + 1 << "->"
								 << "R" << h + 1 << "-(" << c1 << ")*R" << i + 1 << endl;
							for (int w = j; w < n; w++)
							{
								matrix[h][w] = matrix[h][w] - c1 * matrix[i][w];
							}
							display();
						}
					}

					// pivot ko tala ko row haru ko operation
					for (int h = i + 1; h < m; h++)
					{
						float c = matrix[h][j];
						cout << "R" << h + 1 << "->"
							 << "R" << h + 1 << "-(" << c << ")*R" << i + 1 << endl;
						for (int w = j; w < n; w++)
						{
							matrix[h][w] = matrix[h][w] - c * matrix[i][w]; // rn=rn-c*r1
						}
						display();
					}
				}
				else if (pivot == 0)
				{
				}
			}
		}
	}
	getch();
	// ans={{1,3,3},{0,1,2},{0,0,0}}
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
