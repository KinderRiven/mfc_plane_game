#pragma once
#include "GameNature.h"
#include "Resource.h"
class Bullet:
	public GameNature
{
public:
	Bullet(int v,int x,int y);
	Bullet(int v, int x, int y, int dx, int dy);
	//按照子弹的种类进行初始化，并且加上他的初始坐标
	bool is_break();
	void draw(CDC* pDC);
	void change(int sp,int dx,int dy); //改变子弹的方向和速度
	//判断子弹是否飞出界外，如果飞出就删除
	~Bullet();
};