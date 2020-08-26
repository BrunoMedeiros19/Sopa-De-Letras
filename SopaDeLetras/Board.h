#pragma once
#include "Char.h"
#include "Word.h"
#include <iostream>
#include <fstream>
class Board
{
private:
	//atributo das medidas da matriz largura e comprimento
	int BoardWidth;
	int BoardHeight;
	//Atributo que será uma matriz de objectos pertencentes à classe Char
	Char** Chars;
	//Atributo que será um vector de objectos da Classe Word
	Word* Words;
	//atributo que regista o nº de palavras no ficheiro de texto
	int NumWords = 0;
public:
	Board(void);
	void Init(int, int, int dif);
	void View(void);
	~Board();

	inline void Set_BoardWidth(int bw) { BoardWidth = bw; }
	inline void Set_BoardHeight(int bh) { BoardHeight = bh; };
	inline int Get_BoardWidth(void)const { return BoardWidth; }
	inline int Get_BoardHeight(void)const { return BoardHeight; }
	void Insert_Words(int, int);
	inline int Get_Numwords(void)const { return NumWords; }
	inline void Set_Numwords(int num) { NumWords = num; }

	inline string Get_Word(int i) { return Words[i].Get_Letters(); }
	inline int Get_Find(int i) { return Words[i].Get_Find(); }
	inline void Set_Find(int pos, int i) { Words[pos].Set_Find(i);}
	//metodo que vai procurar se existem palavras sobrepostas
	void Verify_Coord(int, int);
	//metodo que verifica se existe algum caracter igual entre 2 palavras e devolve o mesmo
	char Verify_Char(string, string);
	//metodo que vai cruzar as palavras e devolve as coordenadas novas da palavra que cruzamos
	Ponto Reallocate_Words(Word, Word , char);
	//metodo que coloca uma palavra numas coordenas livre da matrz e devolve as coordenadas da palavra mudada
	Ponto Insert_freeSpace(Word,Word, int,int);
	/*Este metodo surgiu pois no final do trabalho existia um bug que quando havia 3 palavras que se cruzavam e
	so duas estavam a ser comparadas se uma delas fosse realoacado noutro sitio da matriz pois era impossivel de cruzar,
	o metodo iria eliminar a palavra na sua posicao antiga o problema é que uma dessas letras pertencia a outra palavra
	deste modo iria haver palavras incompletas para evitar isso cada vez que houver uma mudança , depois dessa mudança
	voltamos a escrever as palavras na matriz nas suas posicoes correctos, ou seja mesmo que fique incompleta quando chamarmos
	este metodo vai voltar a ficar completa*/
	void Update_Matrix(int, int);

	void Save(ofstream&);
	void Read(ifstream&);
};