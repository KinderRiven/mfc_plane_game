#pragma once
#include "GameNature.h"
//#include "Hero.h"
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
//protected:
//	CBitmap bmp;		//图片
//	int width, height;	//模型的大小
//	int x, y;			//位置坐标
//	int speed;			//速度
//	int dir_x, dir_y;	//方向向量
//	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
//	bool is_dead;		//判断是否死亡
//Hero(int num);
//~Hero();
//bool Get_Dir();
//void Hero_Move();	//玩家移动函数
//bool Get_Attack();  //英雄攻击
//void draw_buttle(CDC* cDC); //画子弹
//int  Get_Hit();		//读取攻击信息
//CObList bullet_list;//子弹链表
//int Lv;				//判断英雄的等级，根据等级判断子弹的类型
//int score;			//英雄所持有的分数
//int bound_num;		//大招的个数
//int bullet_num;		//特别子弹的个数
class PersonState:
	public GameNature
{
public:
	PersonState(int num = 1);
	~PersonState();
	void draw(CDC* cDC);
	CBitmap score_bmp;
	int player;
};

