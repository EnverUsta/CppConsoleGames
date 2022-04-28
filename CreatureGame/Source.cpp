#include <iostream>
#include <string>

#include "RandomNumberGeneration.h"
#include "Creature.h"

//TODO List:
//Simple game where you fight monsters
//The goal of the game is to collect as much gold as you can before you die or get to level 20.
//Our program is going to consist of 3 classes:
//Creature
//Player
//Monster
//Player and Monster both inherit from Creature






class Player : public Creature {
private:
	int m_level{ 1 };

public:
	Player(const std::string& name)
		:Creature{ name, '@', 10, 1, 0 }
	{
	}

	void levelUp() {
		++m_level;
		++m_damage;
	}

	int getLevel()const { return m_level; }
	bool hasWon()const { return m_level >= 20; }

};

class Monster: public Creature {
public:
	enum Type {
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};

	struct MonsterData {
		const char *name;
		char symbol;
		int health;
		int damage;
		int gold;
	};

	static MonsterData monsterData[MAX_TYPES];
	
	Monster(Monster::Type type) 
		: Creature{monsterData[type].name, 
			monsterData[type].symbol,
			monsterData[type].health,
			monsterData[type].damage,
			monsterData[type].gold
		}
	{}

	static Monster getRandomMonster() {
		int number{ random::getRandomNumber(0,MAX_TYPES - 1) };
		return Monster{ static_cast<Type>(number) };
	}

};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{"dragon",'D',20, 4, 100},
	{"orc", 'o', 4, 2, 25},
	{"slime", 's', 1, 1, 10}

};

bool lucky(){
	int number = random::getRandomNumber(0, 1);
	if (number == 1) return true;
	else return false;
}


void attackMonster(const Player &p, Monster &m){
	int damageAmount = p.getDamage();
	m.reduceHealth(damageAmount);
	std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage\n";
}

void attackPlayer(Player &p, const Monster &m){
	std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage.\n";
	int damageAmount = m.getDamage();
	p.reduceHealth(damageAmount);

}

void fightMonster(Player &p){
	Monster m = Monster::getRandomMonster();
	std::cout << "You have encountered a " << m.getName() <<'('<<m.getSymbol() << ')'<<'\n';
	bool achievToEscape = false;
	bool killTheMonster = false;
	while(achievToEscape == false && killTheMonster == false){
		if (p.hasWon()) {
			std::cout << "You Won, Congratulations!!!\n";
		}
		if (p.isDead()) {
			std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold\n";
			std::cout << "Too bad you can't take it with you!\n";
			std::cout << "Good By!\n";
			break;
		}
		std::cout << " (R)un or (F)ight: ";
		char choice{};
		std::cin >> choice;
		if (choice == 'r' || choice == 'R') {
			if (lucky()) {
				std::cout << "You succesfully fled\n";
				achievToEscape = true;
			}
			else {
				std::cout << "You failed to flee\n";
				attackPlayer(p, m);
			}
		}
		else {
				attackMonster(p, m);
				attackPlayer(p, m);

				if (m.isDead()) {
					std::cout << "You killed the " << m.getName() << '\n';
					killTheMonster = true;
					std::cout << "You are now level " << p.getLevel() << '\n';
					std::cout << "You found " << m.getGold() << " gold\n";
					p.addGold(m.getGold());
					p.levelUp();
				}
		}
	}
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
	std::rand(); // get rid of first result

	std::cout << "Enter your name: ";
	std::string playerName;
	std::cin >> playerName;

	Player p{ playerName };
	std::cout << "Welcome, " << p.getName() << ".\n";

	while (!p.isDead()) {
		fightMonster(p);
	}
}