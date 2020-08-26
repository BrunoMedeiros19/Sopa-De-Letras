#pragma once
#include "Word.h"
#include <iostream>
using namespace std;

Word::Word()
{
	Set_Letters("");
	Position = Ponto(0, 0);
	Find = 0;
}

Word::Word(string word)
{
	Set_Letters(word);
}

Word::Word(string word, Ponto p1)
{
	Set_Letters(word);
	Set_Position(p1);
}

string Word::Show(void)
{
	return Letters;
}

char Word::Get_Ch(int index)
{
	return Letters[index];
}

void Word::Set_Position(Ponto ponto)
{
	Position = ponto;
}

Ponto Word::Get_Position(void)
{
	return Position;
}

size_t Word::Lenght(void)
{
	return Letters.length();
}


void Word::Set_Letters(string word)
{
	Letters = word;
}

int Word::Get_Orient(void)
{
	return Orientation;
}

void Word::Set_Orient(void)
{
	int random=0;
	random = (rand() % 3) + 1;
	Orientation = random;
}
void Word::Save(ofstream &os)
{
	os << Letters << ",";
}
void Word::Read(ifstream& is)
{
	is >> Letters;
}
Word::~Word()
{
}
