#pragma once
#include "GameNature.h"
//物品的类
//物品大致分为3类，一个是加血，一个加生命，一个加子弹种类
//CBitmap bmp;		//图片
//int width, height;	//模型的大小
//int x, y;			//位置坐标
//int dir_x, dir_y;	//方向向量
//int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
class Things:
	public GameNature
{
public:
	Things(int lv,int x,int y);
	void draw(CDC* pDC);
	void SetPosition();
	void move();
	~Things();
	int Lv;		//定义子弹的种类
	int value;	//定义属性		
	int speed;
};

