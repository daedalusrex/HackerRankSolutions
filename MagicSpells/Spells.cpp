#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
	Fireball* fire = dynamic_cast<Fireball*>(spell);
	Frostbite* frost = dynamic_cast<Frostbite*>(spell);
	Thunderstorm* thunder = dynamic_cast<Thunderstorm*>(spell);
	Waterbolt* water = dynamic_cast<Waterbolt*>(spell);
	
	

	if (fire)
		fire->revealFirepower();
	if (frost)
		frost->revealFrostpower();
	if (thunder)
		thunder->revealThunderpower();
	if (water)
		water->revealWaterpower();

	if (!fire && !frost && !thunder && !water)
	{
		//Dynamic programming required, needs to have a matrix of some kind, 
		//do work over each iteration

		//from size of each strings, plus a null character in each first row to make logic prettier
		int rows = spell->revealScrollName().size() + 1;
		int	cols = SpellJournal::journal.size() + 1;
		
			
		vector<vector<int> > LCS_Mat(rows, vector<int>(cols,0));
		//build matrix left to right
		
		for (int i = 1; i < rows; i++) {
			for (int j = 1; j < cols; j++) {

				//new value = max of above and left
				LCS_Mat[i][j] = max(LCS_Mat[i - 1][j], LCS_Mat[i][j - 1]);
				
				//if chars match add one to LCS(Xs-1,Ys-1), don't forget to account for offset
				if (spell->revealScrollName()[i - 1] == SpellJournal::journal[j - 1])
					LCS_Mat[i][j]= LCS_Mat[i-1][j-1]+1;
			
			}

		}

		//largest possible subsequence should always be at the end of matrix
		cout << LCS_Mat[rows-1][cols-1] << endl;
		
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