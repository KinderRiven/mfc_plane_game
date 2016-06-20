#include "stdafx.h"
#include "Bullet.h"
#include "GameNature.h"
#include "resource.h"
#include "GameMessage.h"
#include "AllSpeed.h"
#include "AllHurt.h"
Bullet::Bullet(int v,int xx,int yy)
{

	bmp.LoadBitmap(4000 + v); //加载不同类型的子弹
	x = xx; y = yy;				 //位置
	dir_x = 0; dir_y = -1;
	is_dead = false; 
	if (v == 1){					 //hero1
		hurt = AllHurt::hurt_b1;					 //计算出每一发子弹的伤害
		width = 27; height = 64;     //大小
		speed = AllSpeed::speed_b1;					 //子弹速度
		//初始化子弹的方向，应该是向上的
	}
	else if (v == 2){				//中型敌机
		hurt = AllHurt::hurt_b2;					//计算出每一发子弹的伤害
		width = 50; height = 101;    //大小
		speed = AllSpeed::speed_b2;					 //子弹速度
		//初始化子弹的方向，应该是向上的
	}
	else if (v == 3){				//小型敌机
		hurt = AllHurt::hurt_b3;
		width = 15; height = 15;
		speed = AllSpeed::speed_b3;
	}
	else if (v == 4){				//闪电子弹
		hurt = AllHurt::hurt_b4;
		width = 27; height = 47;
		speed = AllSpeed::speed_b4;
	}
	else if (v == 5){				
		hurt = AllHurt::hurt_b5;
		width = 20; height = 20;
		speed = AllSpeed::speed_b5;
	}
	else if (v == 6)
	{
		hurt = AllHurt::hurt_b6;
		width = 50; height = 32;
		speed = AllSpeed::speed_b6;
	}
	else if (v == 7)
	{
		hurt = AllHurt::hurt_b7;
		width = 50; height = 50;
		speed = AllSpeed::speed_b7;
	}
	else if (v == 8)
	{
		hurt = AllHurt::hurt_b8;
		width = 43; height = 88;
		speed = AllSpeed::speed_b8;
	}
}
Bullet::Bullet(int v, int xx, int yy, int dx, int dy)
{
	bmp.LoadBitmap(4000 + v); //加载不同类型的子弹
	x = xx; y = yy;			  //位置
	dir_x = dx; dir_y = dy;
	is_dead = false;
	//J
	if (v == 1)
	{
		hurt = AllHurt::hurt_b1;				 //计算出每一发子弹的伤害
		width = 27; height = 64;  //大小
		speed = AllSpeed::speed_b1;					 //子弹速度
		//初始化子弹的方向，应该是向上的
	}
	//敌机中型
	else if (v == 2){
		hurt = AllHurt::hurt_b2;				 //计算出每一发子弹的伤害
		width = 50; height = 101;     //大小
		speed = AllSpeed::speed_b2;					 //子弹速度
		//初始化子弹的方向，应该是向上的
	}
	//敌机小型
	else if (v == 3){
		hurt = AllHurt::hurt_b3;
		width = 8; height = 8;
		speed = AllSpeed::speed_b3;
	}
	//闪电
	else if (v == 4){
		hurt = AllHurt::hurt_b4;
		width = 27; height = 47;
		speed = AllSpeed::speed_b4;
	}
	//BOSS
	else if (v == 5){
		hurt = AllHurt::hurt_b5;
		width = 20; height = 20;
		speed = AllSpeed::speed_b5;
	}
	//爱心
	else if (v == 6)
	{
		hurt = AllHurt::hurt_b6;
		width = 50; height = 32;
		speed = AllSpeed::speed_b6;
	}
	else if (v == 7)
	{
		hurt = AllHurt::hurt_b7;
		width = 50; height = 50;
		speed = AllSpeed::speed_b7;
	}
	else if (v == 8)
	{
		hurt = AllHurt::hurt_b8;
		width = 43; height = 88;
		speed = AllSpeed::speed_b8;
	}
}
Bullet::~Bullet()
{

}
void Bullet::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(238, 243, 250));
	}
}
bool Bullet::is_break(){
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (x < -500 || x > w + 500){
		is_dead = true;
		return true;
	}
	if (y < -500 || y > h + 500){
		is_dead = true;
		return true;
	}
	return false;
}
void Bullet::change(int sp,int dx,int dy)
{
	speed = sp;
	dir_x = dx; dir_y = dy;
}