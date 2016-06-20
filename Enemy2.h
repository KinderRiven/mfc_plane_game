#pragma once
#include "GameMessage.h"
#include "GameNature.h"
class Enemy2:
	public GameNature
{
public:
	Enemy2();
	~Enemy2();
	void draw(CDC* pDC);
	void move();
	void ChangePos();
	void get_dir();
	bool Attack();
	int life;
	int score;
};

