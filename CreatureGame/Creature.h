#pragma once

class Creature {
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_damage;
	int m_gold;

public:
	Creature(const std::string& name, char symbol, int health, int damage, int gold);

	const std::string& getName()const;
	char getSymbol()const;
	int getHealth()const;
	int getDamage()const;
	int getGold()const;
	bool isDead()const;
	void reduceHealth(int reduce);
	void addGold(int gold);

};