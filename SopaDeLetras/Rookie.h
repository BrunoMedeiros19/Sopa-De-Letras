#pragma once
#include "Player.h"
class Rookie :
    public Player
{
public:
    Rookie();
    virtual ~Rookie();
    void Calculate_Score();
};

