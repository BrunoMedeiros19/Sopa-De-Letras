#pragma once
#include "Ponto.h"
#include <iostream>
using namespace std;

Ponto::Ponto() /*Metodo constructor por defeito*/
{
	SetX(0);
	SetY(0);
}
Ponto::~Ponto()/*Metodo destructor*/
{
}

Ponto::Ponto(int mx, int my)/*Metodo constructor por parametros*/
{
	SetX(mx);
	SetY(my);
}

bool Ponto::SetX(int mx)
{
	if (mx >= 0) {
		x = mx;
		return true;
	}
	else
		return false;
}

bool Ponto::SetY(int my)
{
	if (my >= 0) {
		y = my;
		return true;
	}
	else
		return false;
}

bool Ponto::IsValid()
{
	if ((x >= 0) && (y >= 0))
		return true;
	else
		return false;
}

bool Ponto::Ask2Set()
{
	cout << "Int. Valor de 'X':";
	cin >> x;
	cout << "Int. Valor de 'Y':";
	cin >> y;
	return IsValid();
}

void Ponto::Show()
{
	cout << endl << "(" << GetX();
	cout << "," << GetY() << ")";
}

/*Overload do == 
Graças a este metodo podemos comparar coordenadas de pontos diferentes
e se forem iguais retorna true*/
bool Ponto:: operator == (const Ponto P) const
{
	if ((this->GetX() == P.GetX()) && (this->GetY() == P.GetY()))
		return true;
	else
		return false;
}
