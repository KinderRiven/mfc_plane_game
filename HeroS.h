#pragma once
#include "GameNature.h"
class HeroS:
	public GameNature
{
public:
	HeroS(int lv);
	~HeroS();
	void draw(int x,int y,CDC *pDC);
};

