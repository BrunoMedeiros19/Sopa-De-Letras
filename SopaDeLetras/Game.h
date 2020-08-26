#pragma once
#include "Board.h"
#include "Player.h"

using namespace std;
class Game
{
private:
	string nome;
	int score;
	Board PlayBoard;
	string *Words_txt;//vetor que vai ficar guardada as palavras encontradas ou por encontrar dependendo do nivel
	int difficulty;
public:
	Game();
	Game(int, int, string, int);
	int Play();
	inline void Set_Difficulty(int d) { difficulty = d; }
	inline int Get_Difficulty(void)const { return difficulty; }
	//este metodo vai ter um parametro para saber se é rookie ou master a dificuldade
	//0-ROOKIE; 1-MASTER
	void Run();
	bool Find_Word(string);

	inline string Get_Name(void)const { return nome; }
	inline int Get_Score(void)const { return score; }
	inline Board Get_PlayBoard(void) { return PlayBoard; }
	inline string Get_Wordstxt(int i) { return Words_txt[i]; }

	void SaveGame();
	void Read(ifstream&);
	~Game();
};

