#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;
const char live = 'o';
const char dead = ' ';
const int rows = 50;
const int cols = 88;
int count_living_neighbors (char life[rows][cols], int r , int c);

int main ()
{
	char life[rows][cols];
	char temp[rows][cols];
	int cell;
	srand (time (NULL));

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			cell = rand() % 2;
			if (cell == 1)
				life[r][c] = live;
			else
				life[r][c] = dead;
		}
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
			cout << life[r][c] << " ";
		cout << endl;
	}
	usleep(100000);

	while(1)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				int count = count_living_neighbors (life, r, c);
				if (life[r][c] == live)
				{
					if (count == 2 || count == 3)
						temp[r][c] = live;
					else
						temp[r][c] = dead;
				}
				else
				{
					if (count == 3)
						temp[r][c] = live;
					else
						temp[r][c] = dead;
				}
			}
		}

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
				life[r][c] = temp[r][c];
		}

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
				cout << life[r][c] << " ";
			cout << endl;
		}
		usleep(100000);
		system("clear");
	}
	return 0;
}

int count_living_neighbors (char life[rows][cols], int r, int c)
{
	int count = 0;
	bool top = r <= 0;
	bool bottom = r >= (rows - 1);
	bool left = c <= 0;
	bool right = c >= (cols - 1);

	if (!left && life[r][c - 1] == live)
		++count;
	if (!right && life[r][c + 1] == live)
		++count;

	if (!top)
	{
		if (life[r - 1][c] == live)
			++count;
		if (!left && life[r - 1][c - 1] == live)
			++count;
		if (!right && life[r - 1][c + 1] == live)
			++count;
	}

	if (!bottom)
	{
		if (life[r + 1][c] == live)
			++count;
		if (!left && life[r + 1][c - 1] == live)
			++count;
		if (!right && life[r + 1][c + 1] == live)
			++count;
	}

	return count;
}
