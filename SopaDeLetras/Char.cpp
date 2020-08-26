#pragma once
#include "Char.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

Char::Char()
{
	Ch = '\0';
	Position = Ponto(1, 0);
	free = 0;
}

Char::Char(char ch)
{
	Ch = ch;
}

Char::~Char()
{
}

void Char::Rand(void)
{
	char ch = 'A' + rand() % 26; //criacao de um char random neste caso minusculo
	Set_Ch(ch);
}

void Char::View()
{
	cout << Ch;
}
void Char::View_availbpos()
{
	cout << free;
}
void Char::Set_ChPosition(Ponto p)
{
	Position = p;
}
void Char::Convert_Ch(int op)
{
	//converter para maiscula 
	if(op == 1)
	{
		Ch = Ch - 32;
	}
	//minuscula
	else
	{
		Ch = Ch + 32;
	}
}
/*Se for igual a 0 significa que esse char nao pertence a uma palavra
se for 1 significa que pertence*/
void Char::set_free(int f)
{
	free = f;
}
/*Metodo que guarda os caracteres num ficheiro de texto*/
void Char::Save(ofstream& os)
{
	os << Ch << ";";
}
void Char::Read(ifstream& is)
{
	is >> Ch;

}
