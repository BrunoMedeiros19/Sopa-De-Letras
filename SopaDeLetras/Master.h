#pragma once
#include "Player.h"
class Master :
    public Player
{
public:
    Master();
    virtual ~Master();
    void Calculate_Score();
};

