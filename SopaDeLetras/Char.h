#pragma once
#include "Ponto.h"
#include <fstream>

using namespace std;

class Char
{
private:
	char Ch;
	Ponto Position;
	//atributo que nos permite saber se um char pertence a uma palavra ou é random
	int free=0;

public:
	Char();
	Char(char ch);
	~Char();
	
	//metodo para dar um char random
	void Rand(void);
	void View();
	void View_availbpos();
	inline void Set_Ch(char c) { Ch = c; }
	inline char Get_Ch() { return Ch; }
	void Set_ChPosition(Ponto p);
	Ponto Get_ChPosition() { return Position; }
	//este metodo convert os caracteres onde se tiver parametro = 1 é maiscula se for 0 é minuscula
	void Convert_Ch(int );
	void set_free(int);
	int get_free(void)const { return free; }

	void Save(ofstream& os);
	void Read(ifstream& is);
};

