/*
 
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Character
{
private:
	string name;
	int health;
	int attackPower;

public:

	// GETTERS

	string getName() const {
		return name;
	}

	int getHealth() const {
		return health;
	}

	int getAttackPower() const {
		return attackPower;
	}


	// SETTERS
	void setName(const string& newName) {
		name = newName;
	}
	void setHealth(int newHealth) {
		health = newHealth;
	}
	void setAttackPower(int newAttackPower) {
		attackPower = newAttackPower;
	}


	Character(string n, int h, int ap) : name(n), health(h), attackPower(ap) {
		cout << "Character constructor called" << endl;
	}

	virtual void attack(Character& target) {
		cout << "Character attacks!" << endl;
	}

	virtual void isAlive() {
		cout << "Character is alive!" << endl;
	}

	virtual void showStatus() {
		cout << "Character status!" << endl;
	}


	~Character() {
		cout << "Character destructor called" << endl;
	}
};

class Warrior : public Character
{
public:
	Warrior(string warriorName, int warriorHealth, int warriorAttackPower)
		: Character(warriorName, warriorHealth, warriorAttackPower) {
		cout << "Warrior constructor called" << endl;
	}

	void attack(Character& target) override {
		cout << this->getName() << " attacks " << target.getName() << "!" << endl;
		target.setHealth(target.getHealth() - this->getAttackPower());
	}

	void isAlive() override {
		cout << "Warrior is alive!" << endl;
	}

	void showStatus() override {
		cout << "Warrior status!" << endl;
		cout << "Warrior's health is: " << this->getHealth() << endl;
		cout << "Warrior's attack power is: " << this->getAttackPower() << endl;
		cout << "Warrior's name is: " << this->getName() << endl;
		cout << endl;
	}

	~Warrior() {
		cout << "Warrior destructor called" << endl;
	}
};


class Mage : public Character
{
private:
	int mana = 15;

public:
	Mage(string mageName, int mageHealth, int mageAttackPower) : Character(mageName, mageHealth, mageAttackPower) {
		cout << "Warrior constructor called" << endl;
	}
	void attack(Character& target) override {
		cout << this->getName() << " attacks " << target.getName() << "!" << endl;
		target.setHealth(target.getHealth() - this->getAttackPower());
	}
	void isAlive() override {
		cout << "Mage is alive!" << endl;
	}
	void showStatus() override {
		cout << "Mage status!" << endl;
		cout << "Mage's health is: " << this->getHealth() << endl;
		cout << "Mage's attack power is: " << this->getAttackPower() << endl;
		cout << "Mage's name is: " << this->getName() << endl;
		cout << "Mage's mana is: " << this->mana << endl;
		cout << endl;
	}
	void castSpell(Character& target)
	{
		if (mana < 5) {
			cout << "Not enough mana!" << endl;
			return;
		}
		cout << this->getName() <<" casts a spell!" << endl;
		target.setHealth(target.getHealth() - 10); 
		cout << target.getName() << " takes 10 damage!" << endl;
		cout << target.getName() << "'s health is now: " << target.getHealth() << endl;
		mana -= 5; 
		cout << "Mage's mana is now: " << mana << endl;
		cout << "Spell casted!" << endl;
		cout << endl;

	}
	~Mage() {
		cout << "Mage destructor called" << endl;
	}
};

class Archer : public Character
{
public:
	Archer(string archerName, int archerHealth, int archerAttackPower) : Character(archerName, archerHealth, archerAttackPower) {
		cout << "Archer constructor called" << endl;
	}
	void attack(Character& target) override {
		cout << this->getName() << " attacks " << target.getName() << "!" << endl;
		target.setHealth(target.getHealth() - this->getAttackPower());
	}
	void isAlive() override {
		cout << "Archer is alive!" << endl;
	}
	void showStatus() override {
		cout << "Archer status!" << endl;
		cout << "Archer's health is: " << this->getHealth() << endl;
		cout << "Archer's attack power is: " << this->getAttackPower() << endl;
		cout << "Archer's name is: " << this->getName() << endl;
		cout << endl;
	}
	~Archer() {
		cout << "Archer destructor called" << endl;
	}
};

class BattleManager
{
public:
	void startBattle(Character& character1, Character& character2) {
		cout << "Battle started!" << endl;
		character1.attack(character2);
		character2.attack(character1);
	}
	void printWinner(Character& c1, Character& c2)
	{
		if (c1.getHealth() > c2.getHealth()) {
			cout << c1.getName() << " wins!" << endl;
		}
		else if (c1.getHealth() < c2.getHealth()) {
			cout << c2.getName() << " wins!" << endl;
		}
		else {
			cout << "It's a draw!" << endl;
		}
		return;
	}

	void printPlacesOfCharacters(unordered_map<Character*, int>& characterHealth) {
		vector<pair<string, int>> sortedList;

		for (auto& pair : characterHealth) {
			pair.second = pair.first->getHealth();  // Оновлюємо HP
			sortedList.push_back(make_pair(pair.first->getName(), pair.second));
		}

		sort(sortedList.begin(), sortedList.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
			return a.second > b.second;
			});

		int place = 1;
		for (const auto& entry : sortedList) {
			cout << entry.first << " has place #" << place << " with HP: " << entry.second << endl;
			place++;
		}
	}

	void endBattle() {
		cout << "Battle ended!" << endl;
	}
};

class Skill
{
private:
	string skillName;
	int skillPower;
	int manaCost;
public:

	Skill(string name, int power, int cost) : skillName(name), skillPower(power), manaCost(cost)
	{
		cout << "Skill constructor called" << endl;
	}

	void useSkill(Character& user, Character& target) {
		cout << user.getName() << " uses " << skillName << " on " << target.getName() << endl;
		target.setHealth(target.getHealth() - skillPower);
		user.setHealth(user.getHealth() - manaCost);
	}

	~Skill()
	{
		cout << "Skill destructor called" << endl;
	}
};



int main() {
	Warrior* warrior = new Warrior("Warrior", 100, 20);
	Mage* mage = new Mage("Mage", 80, 15);
	Archer* archer = new Archer("Archer", 90, 10);
	BattleManager battleManager;

	unordered_map<Character*, int> characterHealth;
	characterHealth[warrior] = warrior->getHealth();
	characterHealth[mage] = mage->getHealth();
	characterHealth[archer] = archer->getHealth();


	cout << "\n--- GAME START ---\n" << endl;

	warrior->showStatus();
	mage->showStatus();
	archer->showStatus();

	cout << "\n--- ROUND 1 ---\n" << endl;
	warrior->attack(*mage);
	mage->castSpell(*warrior);
	archer->attack(*mage);

	cout << "\n--- STATUS AFTER ROUND 1 ---" << endl;
	cout << warrior->getName() << " HP: " << warrior->getHealth() << endl;
	cout << mage->getName() << " HP: " << mage->getHealth() << endl;
	cout << archer->getName() << " HP: " << archer->getHealth() << endl;

	cout << "\n--- ROUND 2 ---\n" << endl;
	warrior->attack(*archer);
	mage->attack(*warrior);
	archer->attack(*warrior);

	cout << "\n--- STATUS AFTER ROUND 2 ---" << endl;
	cout << warrior->getName() << " HP: " << warrior->getHealth() << endl;
	cout << mage->getName() << " HP: " << mage->getHealth() << endl;
	cout << archer->getName() << " HP: " << archer->getHealth() << endl;

	cout << "\n--- DETERMINING WINNER ---\n" << endl;

	battleManager.printWinner(*warrior, *mage);
	battleManager.printWinner(*warrior, *archer);
	battleManager.printWinner(*mage, *archer);

	
	cout << "\n--- TAKING STOCK ---" << endl;
	battleManager.printPlacesOfCharacters(characterHealth);

	cout << "\n--- GAME OVER ---\n" << endl;

	battleManager.endBattle();


	delete warrior;
	delete mage;
	delete archer;

	return 0;
}
