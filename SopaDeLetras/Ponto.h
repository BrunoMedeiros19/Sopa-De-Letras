#pragma once
class Ponto
{
private:
	int x;
	int y;
public: 
	Ponto();
	Ponto(int, int);
	int GetX() const { return x; }//inline method
	int GetY() const { return y; }
	bool SetX(int);
	bool SetY(int);

	bool IsValid(void);
	bool Ask2Set(void);
	void Show(void);

	bool operator == (const Ponto P) const;

	~Ponto();
};

