#include "stdafx.h"
#include "Hero.h"
#include "resource.h"
#include "GameMessage.h"
#include "Bullet.h"
#include "Game_Lv.h"
#include "AllSpeed.h"
#include "AllHurt.h"
//初始化
Hero::Hero(int num,int p,int cscore)
{
	player = p;		//哪个英雄
	if (player == 1){ //一号玩家控制的英雄
		if (num == 1)
		{
			B_Lv = 1;
			Lv = 1;				//英雄初始的等级为1
			speed = AllSpeed::speed_h1;			 //设定初始的速度
			life = Game_Lv::Hero_Life;		 //设定初始的生命
			bmp.LoadBitmap(num + 2000); //定义飞机类型
			bound_num = 3;		 //初始炸弹
			bullet_num = Game_Lv::Hero_Bullet;//特殊子弹
		}
		else if (num == 2){
			B_Lv = 3;
			Lv = 2;				//英雄初始的等级为1
			speed = AllSpeed::speed_h2;			 //设定初始的速度
			life = 500000;		 //设定初始的生命
			bound_num = 1000;		 //初始炸弹
			bullet_num = 10000;//特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		else if (num == 3)
		{
			B_Lv = 1;
			Lv = 3;				//英雄初始的等级为1
			speed = AllSpeed::speed_h1;			 //设定初始的速度
			life = Game_Lv::Hero_Life;		 //设定初始的生命
			bmp.LoadBitmap(num + 2000); //定义飞机类型
			bound_num = 3;		 //初始炸弹
			bullet_num = Game_Lv::Hero_Bullet;//特殊子弹
		}
		else if (num == 4)
		{
			B_Lv = 3;
			Lv = 4;				 //英雄初始的等级为1
			speed = AllSpeed::speed_h2;//设定初始的速度
			life = 500000;		 //设定初始的生命
			bound_num = 1000;	 //初始炸弹
			bullet_num = 10000;  //特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		hurt = AllHurt::hurt_hero;
		is_dead = false;
		x = 500; y = 500;	 //初始化英雄的位置
		dir_x = 0; dir_y = 0;//初始化方向
		score = cscore;		 //设定初始的的得分为0
		width = 124;		 //飞机宽度
		height = 97;		 //飞机高度
		vk_up    = 'W';		 //定义各种方向键以及技能
		vk_down  = 'S';		vk_a = 'J';  vk_d = 'P';
		vk_left  = 'A';		vk_b = 'K';
		vk_right = 'D';		vk_c = 'L';
	}
	if (player == 2){ //2号玩家控制的英雄
		if (num == 1){
			B_Lv = 1;
			Lv = 1;				//英雄初始的等级为1
			speed = AllSpeed::speed_h1;			 //设定初始的速度
			life = Game_Lv::Hero_Life;		 //设定初始的生命
			bound_num = 3;					 //初始炸弹
			bullet_num = Game_Lv::Hero_Bullet;//特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		else if (num == 2){
			B_Lv = 3;
			Lv = 2;				//英雄初始的等级为1
			speed = AllSpeed::speed_h2;			 //设定初始的速度
			life = 500000;		 //设定初始的生命
			bound_num = 1000;		 //初始炸弹
			bullet_num = 10000;//特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		else if (num == 3)
		{
			B_Lv = 1;
			Lv = 3;				//英雄初始的等级为1
			speed = AllSpeed::speed_h1;			 //设定初始的速度
			life = Game_Lv::Hero_Life;		 //设定初始的生命
			bound_num = 3;					 //初始炸弹
			bullet_num = Game_Lv::Hero_Bullet;//特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		else if (num == 4)
		{
			B_Lv = 3;
			Lv = 4;				//英雄初始的等级为1
			speed = AllSpeed::speed_h2;			 //设定初始的速度
			life = 500000;		 //设定初始的生命
			bound_num = 1000;	  //初始炸弹
			bullet_num = 10000;  //特殊子弹
			bmp.LoadBitmap(num + 2000); //定义飞机类型
		}
		score = cscore;		 //设定初始的的得分为0
		hurt = AllHurt::hurt_hero;
		width = 124; height = 97;
		is_dead = false;
		x = 1000; y = 500;	 //初始化英雄的位置
		dir_x = 0; dir_y = 0;//初始化方向
		vk_up    = VK_UP;		 //定义各种方向键以及技能
		vk_down  = VK_DOWN;
		vk_left  = VK_LEFT;	
		vk_right = VK_RIGHT;
		vk_a = VK_NUMPAD1;
		vk_b = VK_NUMPAD2;
		vk_c = VK_NUMPAD3;
		vk_d = VK_NUMPAD4;
	}
}
//析构函数
Hero::~Hero()
{
}
bool Hero::Get_Dir() //进行移动的判断
{
	if (player == 1)
	{ //玩家1的移动
		if (is_dead) return false;
		if (GetKeyState(vk_up) & 0x8000){
			dir_y = -1; dir_x = 0;
			if (GetKeyState(vk_left) & 0x8000){
				dir_x = -1;
			}
			if (GetKeyState(vk_right) & 0x8000){
				dir_x = 1;
			}
		}
		else if (GetKeyState(vk_down) & 0x8000){
			dir_y = 1; dir_x = 0;
			if (GetKeyState(vk_left) & 0x8000){
				dir_x = -1;
			}
			if (GetKeyState(vk_right) & 0x8000){
				dir_x = 1;
			}
		}
		else if (GetKeyState(vk_left) & 0x8000){
			dir_x = -1;  dir_y = 0;
			if (GetKeyState(vk_up) & 0x8000){
				dir_y = -1;
			}
			if (GetKeyState(vk_down) & 0x8000){
				dir_y = 1;
			}
		}
		else if (GetKeyState(vk_right) & 0x8000){
			dir_x = 1;  dir_y = 0;
			if (GetKeyState(vk_up) & 0x8000){
				dir_y = -1;
			}
			if (GetKeyState(vk_down) & 0x8000){
				dir_y = 1;
			}
		}
		else {
			dir_x = 0;
			dir_y = 0;
			return false;
		}
	}
	if (player == 2)
	{ //玩家1的移动
		if (is_dead) return false;
		if (GetKeyState(vk_up) & 0x8000){
			dir_y = -1; dir_x = 0;
			if (GetKeyState(vk_left) & 0x8000){
				dir_x = -1;
			}
			if (GetKeyState(vk_right) & 0x8000){
				dir_x = 1;
			}
		}
		else if (GetKeyState(vk_down) & 0x8000){
			dir_y = 1; dir_x = 0;
			if (GetKeyState(vk_left) & 0x8000){
				dir_x = -1;
			}
			if (GetKeyState(vk_right) & 0x8000){
				dir_x = 1;
			}
		}
		else if (GetKeyState(vk_left) & 0x8000){
			dir_x = -1;  dir_y = 0;
			if (GetKeyState(vk_up) & 0x8000){
				dir_y = -1;
			}
			if (GetKeyState(vk_down) & 0x8000){
				dir_y = 1;
			}
		}
		else if (GetKeyState(vk_right) & 0x8000){
			dir_x = 1;  dir_y = 0;
			if (GetKeyState(vk_up) & 0x8000){
				dir_y = -1;
			}
			if (GetKeyState(vk_down) & 0x8000){
				dir_y = 1;
			}
		}
		else {
			dir_x = 0;
			dir_y = 0;
			return false;
		}
	}
	return true;
}

int Hero::Get_Hit()
{
	if (is_dead) return 0;
	if (GetKeyState(vk_a) & 0x8000) return 1; //普通攻击
	if (GetKeyState(vk_b) & 0x8000) return 2; //特殊攻击
	if (GetKeyState(vk_c) & 0x8000) return 3; //大招
	if (GetKeyState(vk_d) & 0x8000) return 4; //导弹
	return 0;
}
bool Hero::Get_Attack()
{
	if (is_dead) return false;
	switch (Get_Hit()){
	case 1:
		if (B_Lv == 1)
			bullet_list.AddTail(new Bullet(1, x + width / 2 - 16, y + height / 2 - 30,0,-1)); //生成子弹，并且添加到链表里去
		else if (B_Lv == 2)
		{
			bullet_list.AddTail(new Bullet(1, x + width / 2 - 16, y + height / 2 - 30, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(1, x - 40, y + height / 2 - 30,0,-1)); //生成子弹，并且添加到链表里去
		}
		else if (B_Lv >= 3)
		{
			bullet_list.AddTail(new Bullet(1, x + width / 2 - 16, y + height / 2 - 30, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(1, x - 40, y + height / 2 - 30, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(1, x + 124 + 25, y + height / 2 - 30, 0, -1));
		}
		break;
	case 2:
		if (bullet_num - 3 < 0) break;
		bullet_num -=3;
		if (B_Lv == 1){
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
		}
		else if (B_Lv == 2)
		{
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
		}
		if (B_Lv >= 3)
		{
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(4, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
		}
		break;
	case 3:
		if (bullet_num - 6 < 0) break;
		bullet_num -= 6;
		if (B_Lv == 1){
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
		}
		else if (B_Lv == 2)
		{
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
		}
		if (B_Lv >= 3)
		{
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x, y, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width - 20, y + height, 0, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
			bullet_list.AddTail(new Bullet(6, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
		}
		break;
	case 4:
		if (bound_num <= 0) break;
		bound_num--;
		int w = GameMessage::rect.Width(), h = GameMessage::rect.Height();
		for (int i = 0; i < w; i += 100)
		{
			int j = rand() % 300;
			bullet_list.AddTail(new Bullet(8, i, h + j, 0, -1));
		}
	}
	return true;
}
//飞机子弹的绘制函数
void Hero::draw_buttle(CDC* cDC)
{
	if (bullet_list.IsEmpty())  return;
	POSITION post;
	//链表的遍历
	for (POSITION pos = bullet_list.GetHeadPosition(); (post = pos) != NULL;)
	{
		Bullet* temp = (Bullet*)bullet_list.GetNext(pos);
		if (temp->return_dead()) continue; //如果子弹越界就不进行绘制
		temp->move();					   //移动子弹
		temp->draw(cDC);				   //绘制子弹
		temp->is_break();
		if (temp->return_dead())		   //如果子弹越界
		{
			bullet_list.RemoveAt(post);
			delete temp;
		}
	}
}

void Hero::draw(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead)
	{
		UpDatePos();
		pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(238, 243, 250));
	}
}