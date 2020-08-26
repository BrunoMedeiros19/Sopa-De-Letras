#pragma once
#include <string>
#include <fstream>

#include "Ponto.h"
using namespace std;

class Word
{
private:
	string Letters;
	Ponto Position;
	int Orientation;
	int Find;
public:
	
	Word(void);
	Word(string word);
	Word(string word, Ponto p1);
	string Show(void);

	char Get_Ch(int );

	void Set_Position(Ponto p1);
	Ponto Get_Position(void);
	size_t Lenght(void);
	inline int Get_Find(void)const { return Find; }
	inline void Set_Find(int i) { Find = i; }
	inline string Get_Letters(void)const { return Letters; }
	void Set_Letters(string);
	int Get_Orient(void);
	void Set_Orient(void);
	//get orientarion e set orientation
	~Word();

	void Save(ofstream& os);
	void Read(ifstream& is);
};

