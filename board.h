#include "game.h"
#include <iostream>
using namespace std;

class DungeonBoard 
{
	friend ostream& operator<<(ostream& s, const DungeonBoard& db);

	public:
		DungeonBoard(int _size);
		~DungeonBoard();
		bool Move(char); // Where should I put this, dungeon-board or game? Why is it bool?
		void setX(int);
		void setY(int);
		int getX();
		int getY();
		bool Combat(int pos);
		int getHealth(); 
		int getPower();
		void printCharList();
		void printMonsList();

	private:
		//data
		const int maxTreasures;
		int numTreasures;
		int curCharacter;
		const int maxMobs;
		int numMobs;
		int size;
		char** boardState;
		int** treasures;
		int** mons;
		Monster** mobs; // Monster array
		Party charParty; // Party of characters of type Party
		int xCoord;
		int yCoord;
		int monsterChoice;
		
		//entrance
		int x_enter;
		int y_enter;
		
		//exit
		int x_exit;
		int y_exit;
	
		//functionality
		void setupEntrance();
		void setupTreasure();
		void setupMobs();

};