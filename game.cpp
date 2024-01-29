#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Character::Character() // Default constructor
{
    //srand(time(0));
    health = 80 + (rand() % 21); // 80 - 100
    power = 4 + (rand() % 7); // 4 - 10
    
}

Party::Party() // Default constructor
{
    max = 5;
    current = 5;
    characters = new Character[max];
}

Monster::Monster() // Default constructor
{
    //srand(time(0));
    health = 15 + (rand() % 21);
    power = 1 + (rand() % 6);
    reward = '0';
}

ostream& operator<<(ostream& o, Character c) // Character Insertion operator
{
    o << "Health: " << c.health << endl;
    o << "Power: " << c.power << endl;
    return o;
}

void Party::setX(int x)
{
	xCoord = x;
}

int Party::getX()
{
    return xCoord;
}

void Party::setY(int y)
{
	yCoord = y;
}

int Party::getY()
{
    return yCoord;
}

void Party::setTC(int c) // Add treasure
{
    treasureCounter+=c;
}

int Party::getTC()
{
    return treasureCounter;
}

void Monster::setHealth(int newHealth)
{
    health = newHealth;
}

int Monster::getHealth()
{
    return health;
}

int Party::getHealth()
{
    return health;
}

int Party::getPower()
{
    return power;
}

void Monster::setPower(int newPower)
{
    power = newPower;
}

int Monster::getPower()
{
    return power;
}

int Character::setHealth(int _health)
{
    health = _health;   
}

int Character::getHealth()
{
    return health;
}

int Character::getPower()
{
    return power;
}

void Party::printCharList() // For printing out my list of characters
{
    for (int i = 0; i < current; i++)
    {
        cout << characters[i] << endl;
    }
}

void Party::setCurrent(int _size)
{
    current=_size;
}
int Party::getCurrent()
{
    return current;
}
/*MonsterParty::MonsterParty()
{
    srand(time(0));
    maxSize = 1 + (rand() % 5);
    currentSize = 0;
    list = new Monster[maxSize];
}

MonsterParty::~MonsterParty()
{
    delete [] list;
}*/

// Character* Party::getParty()
// {
//     return characters;
// }

ostream& operator<<(ostream& o, Monster& c)
{
    o << "Health: " << c.health << endl;
    o << "Power: " << c.power << endl;
    
    return o;
}   
