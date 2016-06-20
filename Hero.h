#pragma once
#include "Plane.h"
//玩家控制的飞机的类
//包括英雄的基本属性
class Hero:
	public Plane
{
public:
	Hero(int num, int Player, int cscore = 0);
	~Hero();
	void draw(CDC* pDC);
	bool Get_Dir();
	void Hero_Move();	//玩家移动函数
	bool Get_Attack();  //英雄攻击
	void draw_buttle(CDC* cDC); //画子弹
	int  Get_Hit();		//读取攻击信息
	CObList bullet_list;//子弹链表
	int Lv;				//判断英雄的等级，根据等级判断子弹的类型
	int B_Lv;
	int score;			//英雄所持有的分数
	int bound_num;		//大招的个数
	int bullet_num;		//特别子弹的个数
	int player;
private:
	int vk_up, vk_down, vk_left, vk_right;//飞机移动，上、下、左、右
	int vk_a, vk_b, vk_c,vk_d; //飞机的子弹和特别子弹和大招
};

