#include<iostream>
#include<cstdlib>
#include "board.h"
using namespace std;

// Local declarations
void setBoard(char board[][10]);
void printBoard(char board[][10]);
char printMoveMenu();

int main()
{

	srand(time(0));
	
	//char dungeonBoard[10][10];
	//setBoard(dungeonBoard);
	//printBoard(dungeonBoard);
	DungeonBoard db(10);

	bool alive = true;

	while(alive) // Move the Character
	{
		cout << db << endl;
		cout << "Move the Character..." << endl;
		db.Move(printMoveMenu());
		cout << "\nCHARACTER PARTY STATS\n";
		db.printCharList();
		cout << "MONSTER PARTY STATS\n";
		db.printMonsList();
	}

}

char printMoveMenu()
{
	char userSelection;

	cout << "\n \t \t MOVEMENT DIRECTORY     " << endl;
    cout << "\n \t W \t Move Up";
    cout << "\n \t S \t Move Down";
    cout << "\n \t D \t Move Right";
    cout << "\n \t A \t Move Left";

    cout << "\n> ";
	cin >> userSelection;

	return toupper(userSelection);;
}

void setBoard(char board[][10])
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(i == 0 || i == 9)
			{
				board[i][j]= '-';
				continue;
			} 
			else if (j == 0 || j == 9)
			{
				board[i][j] = '|';
				continue;
			}
			board[i][j] = ' ';
		}
	}
	
	//find the entry
	srand(time(0));
	//pick a number 0-3 to figure out what wall the entrance will be on
	int wall = rand()%4;
	//pick a number 1-8 to figure out what position on that wall the entrance will be at (this keeps the door from being in a corner)
	int pos = rand()%8 + 1;

	switch(wall)
	{
		case 0:
			board[pos][0] = 'X';
			board[pos-1][0] = '-';
			board[pos+1][0] = '-';
			break;
		case 1:
			board[0][pos] = 'X';
			board[0][pos-1] = '|';
			board[0][pos+1] = '|';
			break;
		case 2:
			board[pos][9] = 'X';
			board[pos-1][9] = '-';
			board[pos+1][9] = '-';
			break;
		case 3:
			board[9][pos] = 'X';
			board[9][pos-1] = '|';
			board[9][pos+1] = '|';
			break;
	}
	
	//get 1-3 treasures
	int numTreasures = rand() % 3 + 1;
	for(int i = 0; i < numTreasures; i++)
	{
		//get row
		int row = rand() % 8 + 1;
		//get column
		int column = rand() % 8 + 1;
		//place treasures
		board[row][column] = 'T';
	}
}

void printBoard(char board[][10])
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cout << board[i][j] << "\t";
		}
		cout << endl << endl;
	}
}

// Check for turns - make sure the Character goes first, then the Monsters