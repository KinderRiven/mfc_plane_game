#pragma once
#include "GameNature.h"
//public:
//	GameNature();
//	~GameNature();
//	virtual void draw(CDC* pDC);//画图函数
//	virtual void move();
//	void UpDatePos();
//	bool return_dead();
//	int  return_width();
//	int  return_height();
//	int  return_x();
//	int  return_y();
//	int  return_hurt();
//	void goto_die();
//	int speed;			//速度
//protected:
//	CBitmap bmp;		//图片
//	int width, height;	//模型的大小
//	int x, y;			//位置坐标
//	int dir_x, dir_y;	//方向向量
//	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
//	bool is_dead;		//判断是否死亡
class Enemy3 :
	public GameNature
{
public:
	 Enemy3(int v,int xx,int yy,int dx,int dy);
	~Enemy3();
	void move();
	void Change_Pos();
	void draw(CDC* pDC);
	int life;
	int score;
	int lv;//3号敌机的种类,0右1左2右上3左上
};

