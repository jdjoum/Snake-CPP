#include <iostream>
#include <stdio.h>
#include <conio.h>

bool gameOver;

//Integers representing the size of the game board
const int width = 60;
const int height = 20;

//Integers representing the coordinates of the snake and the fruit, along witht the user score
int x, y, fruitX, fruitY, score;

//Tail Arrays
int tailX[100], tailY[100];
//Tail Elements
int nTail;
//Enum integers represented by direction
//When a key is pressed it corresponds to a direction
enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
//This enum variable can only be one of the values specified above
eDirection dir;


void Setup()
{
	//When the game is intially setup gameOver is set to false
	gameOver = false;
	dir = STOP;
	//This will initially put the snake in the middle of the game board
	x = width / 2;
	y = height / 2;
	//This will randomly assign the fruit a location within the game boundaries
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	//Clears the console screen
	system("cls");
	std::cout << " -------------Welcome to Snake!-------------" << std::endl;
	std::cout << "---------Created By: Julian-Justin Djoum---------" << std::endl;
	std::cout << " ___________________________________________" << std::endl << std::endl;
	//Prints the top boundary of the game board
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//Prints left vertical boundary
			if (j == 0)
				std::cout << "#";
			//Prints spaces
			if (i == y && j == x)
			{
				std::cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				std::cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
			//Prints right vertical boundary
			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	//Prints the bottom boundary of the game board
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	//Prints User Score
	std::cout << "Score: " << score << std::endl;
}

void Input()
{
	//If a keyboard key is pressed...
	if (_kbhit())
	{
		//Returns ASCII Value of pressed character
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//This switch controls the movement of the snake on the gameboard
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	//Handles the rule for staying inside of the boundaries
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	//if (x >= width) x = 0; else if (x < 0) x = width - 1;
	//if (y >= height) y = 0; else if (y < 0) y = height - 1;


	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	//While the game isn't over...
	while (!gameOver)
	{
		Draw();
		Logic();
		Input();
	}
	return 0;
}