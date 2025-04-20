/*
 
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include <chrono>
#include <thread>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"


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

	virtual bool isAlive() {
		cout << "Character is alive!" << endl;
		return this->health > 0;
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

	bool isAlive() override {
		return this->getHealth() > 0;
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
	bool isAlive() override {
		return this->getHealth() > 0;
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
	bool isAlive() override {
		return this->getHealth() > 0;
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


enum CHARACTER_TYPE {
	WARRIOR,
	MAGE,
	ARCHER
};

void myDelay (int numberOfSeconds)
{
	this_thread::sleep_for(chrono::seconds(numberOfSeconds));
}


Character* createCharacter(CHARACTER_TYPE characterType) {
	switch (characterType) {
	case WARRIOR:
		return new Warrior("Warrior", 100, 20);
	case MAGE:
		return new Mage("Mage", 80, 15);
	case ARCHER:
		return new Archer("Archer", 90, 10);
	default:
		return nullptr;
	}
}


int main() {

	// Menu

	cout << "Welcome to the game!" << endl;

	cout << "Please choose your character:" << endl;
	cout << "1. Warrior" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Archer" << endl;

	int userCharacter;
	while (true) {
		cout << "Enter your choice (1-3): ";
		cin >> userCharacter;
		if (userCharacter < 1 || userCharacter > 3) {
			cout << "Invalid choice. Please try again." << endl;
			continue; 
		}
		if (cin.fail()) {
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue; 
		}
		break; 

	}

	Character* userCharacterPtr = nullptr;
	switch (userCharacter)
	{
		case 1:
		cout << "You chose Warrior!" << endl;
		userCharacterPtr = createCharacter(WARRIOR);
		break;
	case 2:
		cout << "You chose Mage!" << endl;
		userCharacterPtr = createCharacter(MAGE);
		break;
	case 3:
		cout << "You chose Archer!" << endl;
		userCharacterPtr = createCharacter(ARCHER);
		break;
	default:
		cout << "Invalid choice!" << endl;
		break;
	}


	myDelay(2);

	Character* randomCharacterPtr = nullptr;
	int randomNumForRandomCharacter = rand() % 3 + 1;
	cout << "Your random character is: " << endl;
	switch (randomNumForRandomCharacter)
	{
	case 1:
		cout <<  "Warrior!" << endl;
		randomCharacterPtr = createCharacter(WARRIOR);
		break;
	case 2:
		cout << "Mage!" << endl;
		randomCharacterPtr = createCharacter(MAGE);
		break;
	case 3:
		cout << "Archer!" << endl;
		randomCharacterPtr = createCharacter(ARCHER);
		break;
	}

	myDelay(2);



	// Game process
	BattleManager battleManager;

	unordered_map<Character*, int> characterHealth;
	characterHealth[userCharacterPtr] = userCharacterPtr->getHealth();
	characterHealth[randomCharacterPtr] = randomCharacterPtr->getHealth();
	cout << "\n--- GAME START ---\n" << endl;
	myDelay(1);
	userCharacterPtr->showStatus();
	randomCharacterPtr->showStatus();
	myDelay(2);

	int roundNumber = 1;
	while (userCharacterPtr->isAlive() && randomCharacterPtr->isAlive()) {
		cout << "\n--- ROUND " << roundNumber <<  " ---\n" << endl;
		userCharacterPtr->attack(*randomCharacterPtr);
		randomCharacterPtr->attack(*userCharacterPtr);
		cout << "\n--- STATUS AFTER ROUND ---" << endl;
		cout << userCharacterPtr->getName() << " HP: " << userCharacterPtr->getHealth() << endl;
		cout << randomCharacterPtr->getName() << " HP: " << randomCharacterPtr->getHealth() << endl;
		roundNumber++;
		myDelay(1); 
	}

	cout << "\n--- DETERMINING WINNER ---\n" << endl;
	myDelay(1);
	
	battleManager.printWinner(*userCharacterPtr, *randomCharacterPtr);


	cout << "\n--- TAKING STOCK ---" << endl;
	myDelay(1);

	battleManager.printPlacesOfCharacters(characterHealth);

	cout << "\n--- GAME OVER ---\n" << endl;
	myDelay(1);
	battleManager.endBattle();
	delete userCharacterPtr;
	delete randomCharacterPtr;


	/*Warrior* warrior = new Warrior("Warrior", 100, 20);
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
	delete archer;*/

	return 0;

}
