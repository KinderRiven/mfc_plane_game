#pragma once
#include "GameNature.h"
#include "GameMessage.h"
class Enemy5:
	public GameNature
{
public:
	Enemy5(int lv,int x, int y, int dx = 1, int dy = 1);
	~Enemy5();
	bool SetPos();
	void move();
	void draw(CDC* pDC);
	bool Attack();
	int life;
	int score;
	int can_attack;
};

