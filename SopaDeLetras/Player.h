#pragma once
#include <iostream>
#include <fstream>
using namespace std;

/*Classe abstracta*/
class Player
{
private:
	string name;
public:
	Player();
	inline void SetName(string n) { name = n; }
	inline string View(void)const { return name; }
	~Player();
	/*Metodo virtual puro, nao pode criar instancias da classe player*/
	virtual void Calculate_Score() = 0;
	void Save(ofstream&);
};

