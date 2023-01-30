#include <iostream>
#include <conio.h>
using namespace std;
#define m 4
#define n 3
float matrix[m][n] = {{1, 2, 3}, {1, 1, 1}, {4, 5, 6}, {7, 8, 9}};

struct pos
{
	int i, j;
};

void display();
void exchange_row(int, int);				 // R1<->R2, exchange two rows
void divide_row(int, float);				 // R=R/c, divide a row with a constant
void multiply_subtract_row(int, int, float); // R1=R1-c*R2, multiply R2 with c and subtract from R1
int is_zero_row(int);						 // returns 1 if given row is zero
void move_zero_row_to_bottom();				 // finds and moves zero row to bottom
void make_zero_above_pivot(int, int);		 // makes all elements above matrix[r][c] into zero
void make_zero_below_pivot(int, int);		 // makes all elements below matrix[r][c] into zero
pos find_next_pivot_below(int, int);		 // returns Position of non zero pivot below or returns Position.i=-1
pos find_next_pivot_right(int, int);		 // returns Position of non zero pivot of right side or returns Position.i=-1

int main()
{
	int i = 0, j = 0;
	pos pivot_position;
	display();
	while (i < m && j < n)
	{
		move_zero_row_to_bottom();
		float pivot = matrix[i][j];
		// cout << "pivot=" << pivot << endl;
		if (pivot == 0)
		{

			pivot_position = find_next_pivot_below(i, j);
			if (pivot_position.i != -1) // if pivot found below
			{
				cout << "Exchange [" << i + 1 << "][" << j + 1 << "]"
					 << " to below \n ";
				exchange_row(i, pivot_position.i);
				pivot = matrix[i][j];
			}
			else // if pivot not found below
			{
				pivot_position = find_next_pivot_right(i, j);
				if (pivot_position.i != -1)
				{
					i = pivot_position.i;
					j = pivot_position.j;
					pivot = matrix[i][j];
				}
				else
				{
					i++;
					j++;
				}
			}
		}
		if (pivot != 0)
		{
			divide_row(i, pivot); // making pivot element 1
			make_zero_above_pivot(i, j);
			make_zero_below_pivot(i, j);
			i++;
			j++;
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

int is_zero_row(int r)
{
	for (int w = 0; w < n; w++)
	{
		if (matrix[r][w] != 0)
			return 0;
	}
	return 1;
}

void move_zero_row_to_bottom()
{
	for (int r = 0; r < m; r++)
	{
		if (is_zero_row(r))
		{
			for (int h = m - 1; h > r; h--)
			{
				if (!is_zero_row(h))
				{
					cout << "Moving zero row to bottom\n";
					exchange_row(r, h);
					break;
				}
			}
		}
	}
}

void make_zero_above_pivot(int pivot_row, int pivot_col)
{
	for (int r = pivot_row - 1; r >= 0; r--)
	{
		if (matrix[r][pivot_col] != 0)
			cout << "Making zero above pivot\n";
		multiply_subtract_row(r, pivot_row, matrix[r][pivot_col]);
	}
}
void make_zero_below_pivot(int pivot_row, int pivot_col)
{
	for (int r = pivot_row + 1; r < m; r++)
	{
		if (matrix[r][pivot_col] != 0)
			cout << "Making zero below pivot\n";
		multiply_subtract_row(r, pivot_row, matrix[r][pivot_col]);
	}
}

pos find_next_pivot_below(int i, int j)
{
	pos P;
	for (int h = i + 1; h < m; h++)
	{
		if (matrix[h][j] != 0)
		{
			P.i = h;
			P.j = j;
			return P;
		}
	}
	P.i = -1;
	return P;
}

pos find_next_pivot_right(int i, int j)
{
	pos P;
	for (int w = j + 1; j < n; j++)
	{
		if (matrix[i][w] != 0)
		{
			P.i = i;
			P.j = w;
			return P;
		}
	}
	P.i = -1;
	return P;
}
