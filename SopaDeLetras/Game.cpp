#pragma once
#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include "graphsettings.h"
#include <vector>

using namespace std;

Game::Game()
{
	nome = "\0";
	score = 0;
}

Game::Game(int w, int h, string name, int dif)
{
	difficulty = dif;
	/*Rookie*/
	if (this->Get_Difficulty() == 0)
	{
		nome = name;
		//inicializa a matriz somento com metade das palavras que existe no txt
		PlayBoard.Init(w, h,0);
		//Inicialização do tamanho do vetor onde vai alocar as 
		//palavras do txt que vai ser igual ao int que esta no txt
		int _size = PlayBoard.Get_Numwords();
		Words_txt = new string[_size];
	}
	else
	{
		nome = name;
		//inicializa a matriz com um minimo de 8 palavras e com nº total par
		PlayBoard.Init(w, h,1);
		int _size = PlayBoard.Get_Numwords();
		Words_txt = new string[_size];
	}
}

void Game::Run()
{
	int x = PlayBoard.Get_BoardHeight();
	int y = PlayBoard.Get_BoardWidth();
	int size = PlayBoard.Get_Numwords();

	/*ROOKIE difficultyFICULTY*/
	/*O numero de palavras para descobrir vai ser metade ou seja como miínimo será 8 palavras no txt
	quando o jogador jogar com esta difficultyiculdade tera de encontrar somente 4 palavras ou seja metade*/
   if(this->Get_Difficulty() == 0)
   {
	   /*enquanto a variavel for menor que o numero de palavras
	o ciclo é executado.*/
	   while (score < size)
	   {
		   setColor(13, 0);
		   cout << "*****ROOKIE MODE****" << endl;
		   resetColor();
		   setColor(2, 0);
		   cout << "Numero de palavras descobertas: " << score;
		   resetColor();
		   setColor(4, 0);
		   cout << " \tNumero de palavras nao descobertas: " << (size - score) << endl;
		   resetColor();
		   cout << endl;

		   /*Uma vez que temos de mostrar as palavras no ecra vamos atribuir a este vetor as palavras que se encontram no txt*/
		   for(int i=0; i < size; i++)
		   {
			   Words_txt[i] = PlayBoard.Get_Word(i);
		   }
		   for (int i = 0; i < size; i++)
		   {
			   cout << "*" << Words_txt[i] << endl;
		   }	   
		   Play();
		   system("pause");
		   system("cls");
	   }
	   setColor(14, 0);
	   cout << "\n\n\t\t______JOGO TERMINADO_______\n" << endl;
	   resetColor();
   }
   /*MASTER DIFFICULTY*/
   else 
   {
	   /*enquanto a variavel for menor que o numero de palavras
	o ciclo é executado.*/
	   while (score < size)
	   {
		   setColor(13, 0);
		   cout << "$$$$ MASTER MODE $$$$" << endl;
		   resetColor();
		   setColor(2, 0);
		   cout << "Numero de palavras descobertas: " << score;
		   resetColor();
		   setColor(4, 0);
		   cout << " \tNumero de palavras nao descobertas: " << (size - score) << endl;
		   resetColor();

		   
		   setColor(12, 0);
		   cout << "\t\t\t\t\t\t\t    TEMPO A CONTAR... ";
		   resetColor();

		   cout << endl;
		   for (int i = 0; i < size; i++)
		   {

			   cout << "*" << Words_txt[i] << endl;

		   }
		   Play();
		   system("pause");
		   system("cls");
	   }
	   setColor(14, 0);
	   cout << "\n\n\t\t______JOGO TERMINADO_______\n" << endl;
	   resetColor();
   }
	
}

int Game::Play()
{
	string palavra;
	SaveGame();
	PlayBoard.View();
	cout << endl;
	setColor(12, 0);
	cout << "Escreva uma palavra da sopa de letras: ";
	resetColor();
	cin >> palavra;
	Find_Word(palavra);
	return 0;
}

/*cada classe deve incluir um metodo save*/
void Game::SaveGame()
{
	/*ADICIONAR MANEIRAS DIFERENTES DE GUARDAR CONSOANTE O NIVEL*/
	/*Cada vez que jogo tenho de guardar a informação da matriz num txt e depois carregar*/
	ofstream os("save-game.txt");
	if (!os)
	{
		cout << "Nao foi possivel guardar no txt a informacao do jogo" << endl;
		exit(0);
	}

	//Vai guardar os atributos dessa classe
	PlayBoard.Save(os);
	//numero de palavras descobertas
	os << "\n" << score << endl;
	//palavras descobertas
	for (int i = 0; i < score; i++)
	{
		os << Words_txt[i] << ";";
	}
	//nome e dificuldade
	os << "\n" << nome << "\n" << difficulty;
	//guardar tempo jogado
	os.close();
}
void Game::Read(ifstream& is)
{	
	PlayBoard.Read(is);//board que fica guardada com todas as informacoes
	string l4;
	/*Este read vai somento ler a ultima linha que é responsavel
	por aparecer as palavras que foram descobertas ate aquele momento*/
	getline(is, l4, '\n');
	score = stoi(l4);
	int numwords = PlayBoard.Get_Numwords();
	//criacao do vetor worrds_txt
	if ((Words_txt = new string[numwords]) == NULL)
	{
		cout << "Nao foi possivel alocar memoria" << endl;
		exit(0);
	}
	for(int i = 0; i < score; i++)
	{
		getline(is, l4, ';');
		Words_txt[i] = l4;
	}
	getline(is, l4, '\n');
	getline(is, l4, '\n');
	nome = l4;
	getline(is, l4, '\n'); getline(is, l4, '\n');
	difficulty = stoi(l4);
}
bool Game::Find_Word(string word)
{
	for(int i = 0; i < PlayBoard.Get_Numwords(); i++)
	{
		if(word == PlayBoard.Get_Word(i) && PlayBoard.Get_Find(i) == 0)
		{
			score++;
			Words_txt[i] = word;
			setColor(2, 0);
			cout << "Palavra encontrada, Parabens faltam somente: " << (PlayBoard.Get_Numwords() - score) << " palavras por encontrar!"<<endl;
			resetColor();
			//coloca essa palavra com atributo find a 1 logo já foi encontrada e n pode ser mais 
			PlayBoard.Set_Find(i,1);
			return true;
		}
		else if(word == PlayBoard.Get_Word(i) && PlayBoard.Get_Find(i) == 1)
		{
			setColor(6, 0);
			cout << "Essa palavra ja foi encontrada! Caso esteja no modo Master verifique na lista de palavras encontradas" << endl;
			resetColor();
			return false;
		}
	}
	setColor(12, 0);
	cout << "Palavra nao encontrada. Verifica se escreves-te bem a palavra!" << endl;
	resetColor();
	return false;
}
Game::~Game(){}