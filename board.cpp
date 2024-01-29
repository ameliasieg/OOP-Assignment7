#include "board.h"
#include <ctime>
#include <cstdlib>

DungeonBoard::DungeonBoard(int _size=10):maxTreasures(_size/2),maxMobs(_size) // Default constructor with initialization list
{
	srand(time(0));
	size = rand()%(4)+5;
	size=_size;
	//allocate a new board
	boardState = new char*[size];
	for(int i = 0; i < size; i++) {
		boardState[i] = new char[size];
		for(int j = 0; j < size; j++) {
			if(i == 0 || i == size-1) {
				boardState[i][j]= '-';
				continue;
			} else if (j == 0 || j == size-1) {
				boardState[i][j] = '|';
				continue;
			}
			boardState[i][j] = ' ';
		}
	}
	
	//set the entrance
	setupEntrance();
	//set the treasures
	setupTreasure();
	//set the mobs
	setupMobs();
}

DungeonBoard::~DungeonBoard() // Destructor
{
	cout << "Destroying game board state..." << endl;
	for(int i = 0; i < size; i++)
	{
		delete [] boardState[i];
	}

	delete [] boardState;
	
	/*cout << "Destroying mob state..." << endl;
	for(int i = 0; i < numMobs; i++) {
		cout << "Destroying mob " << i << endl;
		delete [] mobs[i];
	}*/
	
	cout << "Destroying mob list..." << endl;
	delete [] mobs;
	
	cout << "Destroying treasure state..." << endl;
	for(int i = 0; i < numTreasures; i++)
	{
		cout << "Destroying treasure " << i << endl;
		delete [] treasures[i];
	}

	delete [] treasures;
}

ostream& operator<<(ostream& s, const DungeonBoard& db) // Board Insertion operator
{
	for(int i = 0; i < db.size; i++)
	{
		for(int j = 0; j < db.size; j++)
		{
			s << db.boardState[i][j] << "\t";
		}

		s << endl << endl;
	}
	
	return s;
}

/*ostream& operator<<(ostream& o, Monster m) // Monster Insertion operator
{
    o << "Health: " << m.health << endl;
    o << "Power: " << m.power << endl;
    return o;
}*/

void DungeonBoard::setupEntrance() // Set up the entrance
{
	//find the entry
	//srand(time(0));
	//pick a number 0-3 to figure out what wall the entrance will be on
	int wall = rand() % 4;
	//pick a number 1-8 to figure out what position on that wall the entrance will be at (this keeps the door from being in a corner)
	int pos = rand()%(size-2) + 1;
	
	switch(wall)
	{
		case 0:
			boardState[pos][0] = 'X';
			charParty.setX(0);
			charParty.setY(pos);
			boardState[pos-1][0] = '-';
			boardState[pos+1][0] = '-';
			break;
		case 1:
			boardState[0][pos] = 'X';
			charParty.setX(pos);
			charParty.setY(0);
			boardState[0][pos-1] = '|';
			boardState[0][pos+1] = '|';
			break;
		case 2:
			boardState[pos][size-1] = 'X';
			charParty.setX(size-1);
			charParty.setY(pos);
			boardState[pos-1][size-1] = '-';
			boardState[pos+1][size-1] = '-';
			break;
		case 3:
			boardState[size-1][pos] = 'X';
			charParty.setX(pos);
			charParty.setY(size-1);
			boardState[size-1][pos-1] = '|';
			boardState[size-1][pos+1] = '|';
			break;
	}
}

void DungeonBoard::setupTreasure() // Set up the treasures
{
	numTreasures = rand() % maxTreasures + 5; // Between 5 and 10
	treasures = new int*[numTreasures];
	int amount;

	for(int i = 0; i < numTreasures; i++)
	{
		//get row
		amount = rand() % 10 + 1;
		int row = rand()%(size-2) + 1;
		//get column
		int column = rand()%(size-2) + 1;

		//place treasures
		while(boardState[row][column] == 'T' || row == 0 || row == size - 1 || column == 0 || column == size - 1)
		{	
			row = rand()%(size - 2) + 1;
			column = rand()%(size - 2) + 1;
		}

		boardState[row][column] = 'T';

		treasures[i] = new int[3];
		treasures[i][0] = row;
		treasures[i][1] = column;
		treasures[i][2] = amount;

		cout << "Allocated treasure " << i << endl; 
	}
}

void DungeonBoard::setupMobs() // Set up the monsters
{
	numMobs = rand() % 4 + 5;
	mons = new int*[numMobs];
	mobs = new Monster*[numMobs];

	for(int i = 0; i < numMobs; i++)
	{
		//get row
		int num = rand() % 5+ 1;

		int row = rand()%(size - 2) + 1;
		
		//get column
		int column = rand()%(size - 2) + 1;
		
		//place treasures
		while(boardState[row][column] == 'T' || boardState[row][column] == 'M' || row == 0 || row == size - 1 || column == 0 || column == size - 1)
		{	
			row = rand()%(size - 2) + 1;
			column = rand()%(size - 2) + 1;
		}

		boardState[row][column] = 'M';
	
		mons[i] = new int[3];
		mons[i][0] = row;
		mons[i][1] = column;
		mons[i][2] = num; // Index of monster

		mobs[i] = new Monster[num];

		cout << "Allocated mob " << i << endl;
	}
}

bool DungeonBoard::Move(char c) // Move Function
{
	bool won = false;
	if (c == 'W')
	{
		// Check if I hit the border
		if (boardState[charParty.getY() - 1][charParty.getX()] == '-' || boardState[charParty.getY() - 1][charParty.getX()]== '|')
		{
			cout << "Choose another direction." << endl;
		}
		
		// Check if I hit a monster tile
		if (boardState[charParty.getY() - 1][charParty.getX()] == 'M')
		{	
			for(int i = 0; i < numMobs; i++)
			{
				if(mons[i][0] == charParty.getY() - 1)
				{
					if(mons[i][1] == charParty.getX())
					{
						//cout << mons[i][2];
						won = Combat(mons[i][2]);
					}
				}
			}
			
			if(!won)
				return false;
		}

		// Check if I hit a treasure
		bool found = false;
		if (boardState[charParty.getY() - 1][charParty.getX()] == 'T')
		{
			for(int i = 0; i < numTreasures && !found; i++)
			{
				if(treasures[i][0] == charParty.getY() - 1)
				{	if(treasures[i][1] == charParty.getX())
					{	
						cout << "\nTreasure Value to Add: " << treasures[i][2] << endl;
						charParty.setTC(charParty.getTC() + treasures[i][2]);
						cout << "Treasure Amount: " << charParty.getTC() << endl;
						found = true;
					}	
				}
			}
		}

		// Make sure the spot I leave behind is empty
		boardState[charParty.getY()][charParty.getX()] = ' '; 
		charParty.setY(charParty.getY() - 1);

		// Place an X in my new spot X
		boardState[charParty.getY()][charParty.getX()] = 'X'; 
	}
	
	else if (c == 'S')
	{
		// Check if I hit the border
		if (boardState[charParty.getY() + 1][charParty.getX()] == '-' || boardState[charParty.getY() + 1][charParty.getX()] == '|')
		{
			cout << "Choose another direction." << endl;
		}
		
		// Check if I hit a monster tile
		if (boardState[charParty.getY() + 1][charParty.getX()]== 'M')
		{
			for(int i = 0; i < numMobs; i++)
			{
				if(mons[i][0]==charParty.getY() + 1)
				{
					if(mons[i][1] == charParty.getX())
					{
						won = Combat(mons[i][2]);
					}
				}
			}
			
			if(!won)
				return false;
		}

		// Check if I hit a treasure
		bool found = false;
		if (boardState[charParty.getY() + 1][charParty.getX()] == 'T')
		{
			for(int i = 0; i < numTreasures && !found; i++)
			{
				if(treasures[i][0] == charParty.getY() + 1 )
				{	if(treasures[i][1] == charParty.getX())
					{
						cout << "\nTreasure Value to Add: " << treasures[i][2] << endl;
						charParty.setTC(charParty.getTC() + treasures[i][2]);
						cout << "Treasure Amount: " << charParty.getTC() << endl;
						found = true;
					}	
				}
			}
		}

		// Make sure the spot I leave behind is empty
		boardState[charParty.getY()][charParty.getX()] = ' '; 
		charParty.setY(charParty.getY() + 1);
		// Place an X in my new spot X
		boardState[charParty.getY()][charParty.getX()] = 'X';
	}

	else if (c == 'D')
	{
		// Check if I hit the border
		if (boardState[charParty.getY()][charParty.getX() + 1] == '-' || boardState[charParty.getY()][charParty.getX() + 1] == '|')
		{
			cout << "Choose another direction." << endl;
		} 
		
		// Check if I hit a monster tile
		if (boardState[charParty.getY()][charParty.getX() + 1] == 'M')
		{
			for(int i = 0; i < numMobs; i++)
			{
				if(mons[i][0] == charParty.getY() )
				{
					if(mons[i][1] == charParty.getX()+1)
					{
						won = Combat(mons[i][2]);
					}
				}
			}
			
			if(!won)
				return false;

		}

		// Check if I hit a treasure
		bool found = false;
		if (boardState[charParty.getY()][charParty.getX() + 1] == 'T')
		{
			for(int i = 0; i < numTreasures && !found; i++)
			{
				if(treasures[i][0] == charParty.getY() )
				{	if(treasures[i][1] == charParty.getX() + 1 )
					{
						cout << "\nTreasure Value to Add: " << treasures[i][2] << endl;
						charParty.setTC(charParty.getTC() + treasures[i][2]);
						cout << "Treasure Amount: " << charParty.getTC() << endl;
						found = true;
					}	
				}
			}
		}

		// Make sure the spot I leave behind is empty
		boardState[charParty.getY()][charParty.getX()] = ' '; 
		charParty.setX(charParty.getX() + 1);

		// Place an X in my new spot X
		boardState[charParty.getY()][charParty.getX()] = 'X';
	}

	else if (c == 'A')
	{
		// Check if I hit the border
		if (boardState[charParty.getY()][charParty.getX()-11] == '-' || boardState[charParty.getY() ][charParty.getX()-1]== '|')
		{
			cout << "Choose another direction." << endl;
		} 
		
		// Check if I hit a monster tile
		if (boardState[charParty.getY()][charParty.getX()-1] == 'M')
		{
			for(int i = 0; i < numMobs; i++)
			{
				if(mons[i][0] == charParty.getY())
				{
					if(mons[i][1] == charParty.getX() - 1)
					{
						won = Combat(mons[i][2]);
					}
				}
			}
			
			if(!won)
				return false;

		}

		// Check if I hit a treasure
		bool found = false;
		if (boardState[charParty.getY()][charParty.getX()-1] == 'T')
		{
			for(int i = 0; i < numTreasures && !found; i++)
			{
				if(treasures[i][0] == charParty.getY() )
				{	
					if(treasures[i][1] == charParty.getX() - 1 )
					{
						cout << "\nTreasure Value to Add: " << treasures[i][2] << endl;
						charParty.setTC(charParty.getTC() + treasures[i][2]);
						cout << "Treasure Amount: " << charParty.getTC() << endl;
						found = true;
					}	
				}
			}		
		}

		// Make sure the spot I leave behind is empty
		boardState[charParty.getY()][charParty.getX()] = ' '; 
		charParty.setX(charParty.getX() - 1);
		// Place an X in my new spot X
		boardState[charParty.getY()][charParty.getX()] = 'X';
		
	}
}

bool DungeonBoard::Combat(int pos) // Combat function
{
	
	int characterChoice;
	int monsterChoice;
	bool escape = false; // For running away
	int choice; // For if they want to fight again or run away
	char c;
	
	cout << "\nYou have come into contact with a monster! Do you want to attack or run away?" << endl;
	cout << "\n\t\t COMBAT DIRECTORY\n" << endl;
	cout << "\t A \t Run Away\n\t B \t Attack\n> ";
	cin >> c;
	toupper(c);

	if(c == 'A' )
		return false;

	if(c != 'B')
	{
		/*cout << "INVALID CHOICE!\n>";*/

		while(c != 'B' && c != 'A')
		{	cout << "INVALID CHOICE!\n> ";
			cin >> c;
			toupper(c);
		}
	}

	if(c=='A' )
		return false;

	cout << "Which character do you want to use? ( 0 - "<<charParty.getCurrent()<<" ): ";
	cin >> characterChoice;
	cout << "Which monster would you like to hit? (0 - " << mons[pos][2] << "): ";
	cin >> monsterChoice;

	
	
	while(  charParty.characters[characterChoice].getHealth() > 0 && mons[pos][2]>0)
	{

		int monsterPercentage = rand() % 100 + 1; // A number between 1 and 100
		int characterPercentage = rand() % 100 + 1; // A number between 1 and 100
		if (characterPercentage > 15)
		{
			// Character attack hits - monster health decreases by character's power
			cout << "You hit the monster!" << endl;
			mobs[pos][monsterChoice].setHealth(mobs[pos][monsterChoice].getHealth() - charParty.characters[characterChoice].getPower());
		}
		else
		{
			// Character attack misses - do nothing
			cout << "You missed the monster!" << endl;
		}

		if (monsterPercentage > 50)
		{
			// If the monster's attack hits, the monster's power should be subtracted from the character's health
			cout << "You hit the character!" << endl;
			charParty.characters[characterChoice].setHealth(charParty.characters[characterChoice].getHealth() - mobs[pos][monsterChoice].getPower());
		}
		else 
		{
			// Monster attack misses
			cout << "You missed the character!" << endl;
		}

		cout << "\nCHARACTER PARTY STATS\n";
		for(int i=0;i<charParty.getCurrent();i++)
		{
			cout<<charParty.characters[i]<<endl;
		}

		cout << "MONSTER PARTY STATS\n";
		for(int i=0;i<mons[pos][2];i++)
		{
			cout<<mobs[pos][i]<<endl;
		}
		
		// // if(charParty.getHealth() <=0  && charParty.getCurrent()>0 )
		// // {
		// // 	charParty.setCurrent(charParty.getCurrent()-1);
		// // 	cout << "Character has been defeated!\nWould you like to use another one? Or would you like to escape? ( 0 - " << 
		// // 	charParty.getCurrent() <<endl;
		// // 	cin >> choice;

		// // 	while(charParty.getHealth()<=0 )
		// // 	{
		// // 	cout << "Character has been defeated!\nWould you like to use another one? Or would you like to escape? ( 0 - " << 
		// // 	charParty.getCurrent() <<endl;
		// // 	cin >> choice;

		// // 	}

		// 	characterChoice=choice;
		// }



		// if(mobs[pos][monsterChoice].getHealth() <= 0)
		// {
		// 	mons[pos][2]--;
		// 	cout << "Monster has been defeated!\nWould you like to fight another one? Or would you like to escape? ( 0 - " << 
		// 	mons[pos][2] <<endl;
		// 	cin >> choice;

		// 	while(mobs[pos][choice].getHealth()<=0 && mons[pos][2]>0 )
		// 	{
		// 	cout << "Monster has been defeated!\nWould you like to fight another one? Or would you like to escape? ( 0 - " << 
		// 	mons[pos][2] <<endl;
		// 	cin >> choice;
		// 	}

		// 	cout << "> ";
			

		// 	if(choice == 1)
		// 		cin >> monsterChoice;

		// 	if(choice == 2)
		// 		return false;
		// }



	
	cout << "\t A \t Run Away\n\t B \t Attack\n> ";
	cin >> c;
	toupper(c);

	if(c == 'A' )
		return false;

	if(c != 'B')
	{
		/*cout << "INVALID CHOICE!\n>";*/

		while(c != 'B' && c != 'A')
		{	cout << "INVALID CHOICE!\n> ";
			cin >> c;
			toupper(c);
		}
	}

	if(c=='A' )
		return false;
	}

	if(escape)
		return false;

	if(charParty.characters[characterChoice].getHealth() <= 0 )
		return false;

	else
		return true;

}

void DungeonBoard::printCharList() // For printing out my list of characters
{
	charParty.printCharList();

}

void DungeonBoard::printMonsList()
{

	for (int i = 0; i < numMobs; i++)
    {
		for(int j=0;j<mons[i][2];j++)
        cout << mobs[i][j] << endl;
    }
}