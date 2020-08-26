#include "Player.h"

Player::Player()
{
	name = "";
}

Player::~Player()
{
}

//Guarda o nome do Jogador
void Player::Save(ofstream& os)
{
	os << name;
}
