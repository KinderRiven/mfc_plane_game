#pragma once
#include "GameNature.h"
//飞机的大类
class Plane:
	public GameNature
{
public:
	Plane();
	~Plane();
	int life;  //生命
};
