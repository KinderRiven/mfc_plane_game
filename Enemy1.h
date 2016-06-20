#pragma once
#include "GameNature.h"
class Enemy1:
	public GameNature
{
public:
	Enemy1();
	~Enemy1();
	void move();
	void Change_Dir();
	void draw(CDC* cDC);
	bool Attack(); //·¢Éä×Óµ¯
	int life;
	int score;
};

