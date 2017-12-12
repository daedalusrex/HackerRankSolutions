#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
private:
	string scrollName;
public:
	Spell() : scrollName("") { }
	Spell(string name) : scrollName(name) { }
	virtual ~Spell() { }
	string revealScrollName() {
		return scrollName;
	}
};

class Fireball : public Spell {
private: int power;
public:
	Fireball(int power) : power(power) { }
	void revealFirepower() {
		cout << "Fireball: " << power << endl;
	}
};

class Frostbite : public Spell {
private: int power;
public:
	Frostbite(int power) : power(power) { }
	void revealFrostpower() {
		cout << "Frostbite: " << power << endl;
	}
};

class Thunderstorm : public Spell {
private: int power;
public:
	Thunderstorm(int power) : power(power) { }
	void revealThunderpower() {
		cout << "Thunderstorm: " << power << endl;
	}
};

class Waterbolt : public Spell {
private: int power;
public:
	Waterbolt(int power) : power(power) { }
	void revealWaterpower() {
		cout << "Waterbolt: " << power << endl;
	}
};

class SpellJournal {
public:
	static string journal;
	static string read() {
		return journal;
	}
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {


	/* Enter your code here */
	//use dynmaic cast for type conversion, and then just default case it must be generic
	Fireball* fire = dynamic_cast<*Fireball>(spell);
	Frostbite* frost = dynamic_cast<*Frostbite>(spell);
	Thunderstorm* thunder = dynamic_cast<*Thunderstorm>(spell);
	Waterbolt* water = dynamic_cast<*Waterbolt>(spell);
	

	if (fire)
		fire->revealFirepower;
	if (frost)
		frost->revealFrostpower;
	if (thunder)
		thunder->revealThunderpower;
	if (water)
		water->revealWaterpower;

	if (!fire && !frost && !thunder && !water)
	{
		//decode which one is the best 

		//If it is a generic spell, find a subsequence of letters that are contained in both the spell name and your
		//	spell journal.Among all such subsequences, find and print the length of the longest one on a new line.

		//AquaVitae is not, and when you compare it with AruTaVae in your spell journal, you get a sequence:
		//		AuaVae


		//huh, apears to be some kind of longest common subsequence not trivial at all.
	}


}

class Wizard {
public:
	Spell * cast() {
		Spell *spell;
		string s; cin >> s;
		int power; cin >> power;
		if (s == "fire") {
			spell = new Fireball(power);
		}
		else if (s == "frost") {
			spell = new Frostbite(power);
		}
		else if (s == "water") {
			spell = new Waterbolt(power);
		}
		else if (s == "thunder") {
			spell = new Thunderstorm(power);
		}
		else {
			spell = new Spell(s);
			cin >> SpellJournal::journal;
		}
		return spell;
	}
};

int main() {
	int T;
	cin >> T;
	Wizard Arawn;
	while (T--) {
		Spell *spell = Arawn.cast();
		counterspell(spell);
	}
	return 0;
}