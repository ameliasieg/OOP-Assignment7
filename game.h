#include <iostream>
using namespace std;

class Character
{
    friend ostream& operator<<(ostream&, Character); // Insertion operator
 
    public:
    Character(); // Default constructor
    int getHealth();
    int getPower();
    int setHealth(int _health);
    // Do I need a setPower(int)?
 
    private:
    int health; // Shows current health of character. If value goes <= 0, character dies and is removed
    int power; // Shows current power of character. When attacking, this is the amount to be removed from Monster's health
};

class Party // Container class - can have up to 5 instances of characters
{
    friend ostream& operator<<(ostream& s, const Party& p);
    
    public:
    Party();
    void setX(int);
	void setY(int);
    int getX();
    int getY();
    void setTC(int c);
    int getTC();
    int getHealth();
    int getPower();
    void setCurrent(int _size);
    int getCurrent();
    //int Combat();
    void printCharList(); // Prints the list of characters in the party
    Character* characters;

    private:
    int current;
    int max;
    int xCoord;
    int yCoord;
    int health;
    int power;
    int treasureCounter; // Treasure counter
};

class Monster
{   friend ostream& operator<<(ostream& o, Monster& c);
    public:
    Monster(); // Default constructor
    //int Combat();
    int GetDamage();
    void setX(int);
    void setY(int);
    void setHealth(int);
    void setPower(int);
    int getHealth();
    int getPower();

    private:
    int health;
    int power;
    int reward;
};

/*class MonsterParty // DMA
{
    public:
    MonsterParty(); // Default constructor
    ~MonsterParty(); // Destructor
    void setX(int);
	void setY(int);
    int getX();
    int getY();

    private:
    int maxSize;
    int currentSize;
    Monster* list;

};*/