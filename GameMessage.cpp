#include "stdafx.h"
#include "GameMessage.h"
#include "GameNature.h"
#include "BackGround.h"
#include "Hero.h"
#include "HeroS.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Bullet.h"
#include "GameWord.h"
#include "Explo.h"
#include "PersonState.h"
#include "resource.h"
#include "BOSS1.h"
#include "Game_Lv.h"
#include "GameContrl.h"
#include "AllHurt.h"
#include "AllLife.h"
#include "AllScore.h"
#include "AllSpeed.h"
#include "GameLevel.h"
#include "Things.h"

GameMessage::GameMessage()
{
}

GameMessage::~GameMessage()
{
}
//画背景
void GameMessage::ShowBackground(CDC* cDC)
{
	if (is_talking)		//谈话模式
	{
		talkground->draw(cDC);
		return;
	}
	if (step == -2 && boombackground != NULL)
	{
		boombackground->move();
		boombackground->PaintPicture2(cDC);
		boombackground2->move();
		boombackground2->PaintPicture2(cDC);
	}
	if (is_stop) return; //暂停停止刷新
	if (background == NULL) return;
	background->move();
	background->PaintPicture(cDC);
}
//画玩家的函数
void GameMessage::ShowHero(CDC *cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (hero == NULL && hero2 == NULL && Hero_Life <= 0 && Hero2_Life <= 0 && step != -1)
	{
		step = -3;
		next_step = -1;
		return;
	}
	if (hero == NULL && Hero_Life > 0)
	{
		Hero_Life--;
		hero  = new Hero(Hero_Kind,1,Hero_score);
		L_Hero = new HeroS(Hero_Kind);
	}
	else if (hero == NULL && Hero_Life <= 0)
	{
		
	}
	if (hero2 == NULL && Hero2_Life > 0)
	{
		Hero2_Life--;
		hero2  =  new Hero(Hero2_Kind, 2,Hero2_score);
		L_Hero2 = new HeroS(Hero2_Kind);
	}
	else if (hero2 == NULL && Hero2_Life <= 0)
	{

	}
	if (hero != NULL)
	{
		hero->Get_Dir();		//获取移动方向
		hero->move();			//进行移动
		hero->draw_buttle(cDC); //绘制子弹链表
		hero->draw(cDC);
		int x = hero->return_x(), y = hero->return_y();
		if (hero->B_Lv >= 2)
		{
			L_Hero->draw(x - 60, y + 20, cDC);
		}
		if (hero->B_Lv >= 3)
		{
			L_Hero->draw(x + 124, y + 20, cDC);
		}
	}//进行绘制
	if (hero2 != NULL)
	{
		hero2->Get_Dir();		//获取移动方向
		hero2->move();			//进行移动
		hero2->draw_buttle(cDC); //绘制子弹链表
		hero2->draw(cDC);
		int x = hero2->return_x(), y = hero2->return_y();
		if (hero2->B_Lv >= 2)
		{
			L_Hero2->draw(x - 60, y + 20, cDC);
		}
		if (hero2->B_Lv >= 3)
		{
			L_Hero2->draw(x + 124, y + 20, cDC);
		}
	}
}
//状态窗口的绘制
void GameMessage::ShowState(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (hero != NULL){
		if (state1 == NULL) state1 = new PersonState(1);
		if (state1 != NULL)
		{
			int w = rect.Width(), h = rect.Height();
			state1->draw(cDC);			 //画状态
			//生命值
			int v = hero->life;
			CString _word;
			_word.Format(L"%d", v);
			//GameWord(CString w, int start, int end, int x, int y);
			//贴子弹数
			Word_List.AddTail(new GameWord(_word, 10, 10, 165, 20));
			_word.Format(L"无限");
			Word_List.AddTail(new GameWord(_word, 10, 10, 165, 51));
			//特别子弹个数
			v = hero->bullet_num;
			_word.Format(L"   %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, 165, 80));
			//大招
			v = hero->bound_num;
			_word.Format(L"   %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, 165, 105));
			//得分
			v = hero->score;
			_word.Format(L"  %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, 45, h - 25));
		}
	}
	if (hero2 != NULL)
	{
		if (state2 == NULL) state2 = new PersonState(2);
		if (state2 != NULL)
		{
			int ww = rect.Width(), hh = rect.Height();
			state2->draw(cDC);			 //画状态
			//生命值
			int v = hero2->life;
			CString _word;
			_word.Format(L"%d", v);
			//GameWord(CString w, int start, int end, int x, int y);
			//贴子弹数
			int w = rect.Width();
			int h = rect.Height();
			Word_List.AddTail(new GameWord(_word, 10, 10, ww - 55, 20));
			_word.Format(L"无限");
			Word_List.AddTail(new GameWord(_word, 10, 10, ww - 45, 51));
			//特别子弹个数
			v = hero2->bullet_num;
			_word.Format(L"   %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, ww - 55, 80));
			//大招
			v = hero2->bound_num;
			_word.Format(L"   %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, ww - 55, 105));
			//得分
			v = hero2->score;
			_word.Format(L"  %d", v);
			Word_List.AddTail(new GameWord(_word, 10, 10, ww - 55, h - 25));
		}
	}
}
//获得攻击消息
void GameMessage::GetKeyAttack()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (hero != NULL)
	{
		hero->Get_Attack();		//进行攻击消息的收集
	}
	if (hero2 != NULL)
	{
		hero2->Get_Attack();
	}
}
//敌机的绘制
void GameMessage::ShowEnemy1(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy1_List.IsEmpty()) return; //没有敌人
	POSITION post;
	for (POSITION pos = Enemy1_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy1* temp = (Enemy1*)Enemy1_List.GetNext(pos);
		temp->move();			//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			int e = rand() % (GameLevel::Thing_drop + 3); //
			if (e == 1){
				int t = rand() % 4 + 1; //随机产生4种物品
				Things_List.AddTail(new Things(t, temp->return_x(), temp->return_y()));
			}
			Enemy1_List.RemoveAt(post);
			delete temp;
		}
		else if (temp->Attack())
		{
			int x = temp->return_x(), y = temp->return_y();
			int w = temp->return_width(), h = temp->return_height();
			Bullet* tmp = new Bullet(2, x + w / 2 - 38, y + h - 20);
			tmp->change(40, 0, 1);
			Enemy_Bullet_List.AddTail(tmp);
		}
	}
}
void GameMessage::ShowEnemy2(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy2_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Enemy2_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy2* temp = (Enemy2*)Enemy2_List.GetNext(pos);
		temp->move();			//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			int e = rand() % (GameLevel::Thing_drop + 10); //
			if (e == 0){
				int t = rand() % 4 + 1; //随机产生4种物品
				Things_List.AddTail(new Things(t, temp->return_x(), temp->return_y()));
			}
			Enemy2_List.RemoveAt(post);
			delete temp;
		}
		else if (temp->Attack())
		{
			int x = temp->return_x(), y = temp->return_y();
			int w = temp->return_width(), h = temp->return_height();
			Bullet* tmp = new Bullet(3, x + w / 2 - 38, y + h - 20);
			int dx = rand() % 3, dy = 1;
			dx -= 1;
			tmp->change(15,dx, dy);
			Enemy_Bullet_List.AddTail(tmp);
		}
	}
}
void GameMessage::ShowEnemy3(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy3_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Enemy3_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy3* temp = (Enemy3*)Enemy3_List.GetNext(pos);
		temp->move();		//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			int e = rand() % (GameLevel::Thing_drop + 10); //
			if (e == 3){
				int t = rand() % 4 + 1; //随机产生4种物品
				Things_List.AddTail(new Things(t, temp->return_x(), temp->return_y()));
			}
			Enemy3_List.RemoveAt(post);
			delete temp;
		}
	}
}
void GameMessage::ShowEnemy4(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy4_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Enemy4_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy4* temp = (Enemy4*)Enemy4_List.GetNext(pos);
		temp->move();		//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			int e = rand() % (GameLevel::Thing_drop + 3); //
			if (e == 3){
				int t = rand() % 4 + 1; //随机产生4种物品
				Things_List.AddTail(new Things(t, temp->return_x(), temp->return_y()));
			}
			Enemy4_List.RemoveAt(post);
			delete temp;
		}
	}
}
void GameMessage::ShowEnemy5(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy5_List.IsEmpty()) return; //没有敌人
	POSITION post;
	for (POSITION pos = Enemy5_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy5* temp = (Enemy5*)Enemy5_List.GetNext(pos);
		temp->move();			//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			Things_List.AddTail(new Things(1, temp->return_x(), temp->return_y()));
			int e = rand() % (GameLevel::Thing_drop + 5);
			if (e == 1){
				int t = rand() % 4 + 1; //随机产生4种物品
				Things_List.AddTail(new Things(t, temp->return_x(), temp->return_y()));
			}
			Enemy5_List.RemoveAt(post);
			delete temp;
		}
		else if (temp->Attack())
		{
			int x = temp->return_x(), y = temp->return_y();
			int width = temp->return_width(), height = temp->return_height();
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
			Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
		}
	}
}
void GameMessage::ShowEnemyBoss(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Boss_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Boss_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		BOSS1* temp = (BOSS1*)Boss_List.GetNext(pos);
		temp->move();			//敌机移动
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			Things_List.AddTail(new Things(1, temp->return_x(), temp->return_y()));
			Boss_List.RemoveAt(post);
			delete temp;
		}
		else if (temp->Attack())
		{
			int x = temp->return_x(), y = temp->return_y();
			int width = temp->return_width(), height = temp->return_height();
			if (temp->Lv <= 3){
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			}
			else if (temp->Lv == 4)
			{
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(7, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			}
			else if (temp->Lv == 5)
			{
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 0, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 0)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, -1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, 1, 1)); //生成子弹，并且添加到链表里去
				Enemy_Bullet_List.AddTail(new Bullet(5, x + width / 2 - 16, y + height / 2 - 15, -1, -1)); //生成子弹，并且添加到链表里去
			}
		}
	}
}
void GameMessage::ShowWord(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (step == -3)return;
	if (Word_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Word_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		GameWord* temp = (GameWord*)Word_List.GetNext(pos);
		temp->draw(cDC);
		if (temp->start > temp->end)
		{
			Word_List.RemoveAt(post);
			delete temp;
		}
	}
}
void GameMessage::ShowExplo(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Explo_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Explo_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Explo* temp = (Explo*)Explo_List.GetNext(pos);
		if (temp->return_dead()) continue;
		temp->draw(cDC);		//画出飞机
		if (temp->return_dead())
		{
			Explo_List.RemoveAt(post);
			delete temp;
		}
	}
}
void GameMessage::ShowEnemyBullet(CDC* cDC)
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	if (Enemy_Bullet_List.IsEmpty())  return;
	POSITION post;
	//链表的遍历
	for (POSITION pos = Enemy_Bullet_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Bullet* temp = (Bullet*)Enemy_Bullet_List.GetNext(pos);
		if (temp->return_dead()) continue; //如果子弹越界就不进行绘制
		temp->move();						//移动子弹
		temp->draw(cDC);					//绘制子弹
		temp->is_break();
		if (temp->return_dead())			//如果子弹越界
		{
			Enemy_Bullet_List.RemoveAt(post);
			delete temp;
		}
	}
}
//子弹攻击敌人
void GameMessage::EnemyAttack1()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		//进行一号敌机机群的判断
		if (hero->bullet_list.IsEmpty());
		else{
			if (Enemy1_List.IsEmpty());
			else{
				for (POSITION pos1 = Enemy1_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					Enemy1* temp1 = (Enemy1*)Enemy1_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3,C1,C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 30));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								Explo_List.AddTail(new Explo(2, x1 + 55, y1));
								Explo_List.AddTail(new Explo(2, x1, y1 + 68));
								Explo_List.AddTail(new Explo(2, x1 + 46, y1 + 60));
								temp1->goto_die();
							}
							//减血判断是否死亡
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		if (hero2->bullet_list.IsEmpty()) return;
		if (Enemy1_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy1_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Enemy1* temp1 = (Enemy1*)Enemy1_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3,C1,C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 30));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						Explo_List.AddTail(new Explo(2, x1 + 55, y1));
						Explo_List.AddTail(new Explo(2, x1, y1 + 68));
						Explo_List.AddTail(new Explo(2, x1 + 46, y1 + 60));
						temp1->goto_die();
					}
					//减血判断是否死亡
				}
			}
		}
	}
}
void GameMessage::EnemyAttack2()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		//进行一号敌机机群的判断
		if (hero->bullet_list.IsEmpty());
		else{
			if (Enemy2_List.IsEmpty());
			else{
				for (POSITION pos1 = Enemy2_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					Enemy2* temp1 = (Enemy2*)Enemy2_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3,C1,C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 30));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								Explo_List.AddTail(new Explo(2, x1 + 55, y1));
								Explo_List.AddTail(new Explo(2, x1 + 46, y1 + 60));
								temp1->goto_die();
							}
							//减血判断是否死亡
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		//进行一号敌机机群的判断
		if (hero2->bullet_list.IsEmpty()) return;
		if (Enemy2_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy2_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Enemy2* temp1 = (Enemy2*)Enemy2_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3,C1,C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 30));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						Explo_List.AddTail(new Explo(2, x1 + 55, y1));
						Explo_List.AddTail(new Explo(2, x1 + 46, y1 + 60));
						temp1->goto_die();
					}
					//减血判断是否死亡
				}
			}
		}
	}
}
void GameMessage::EnemyAttack3()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		if (hero->bullet_list.IsEmpty());
		else{
			if (Enemy3_List.IsEmpty());
			else{
				for (POSITION pos1 = Enemy3_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					Enemy3* temp1 = (Enemy3*)Enemy3_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3,C1,C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 50));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								temp1->goto_die();
							}
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		if (hero2->bullet_list.IsEmpty()) return;
		if (Enemy3_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy3_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Enemy3* temp1 = (Enemy3*)Enemy3_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3,C1,C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 50));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						temp1->goto_die();
					}
				}
			}
		}
	}
}
void GameMessage::EnemyAttack4()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		if (hero->bullet_list.IsEmpty());
		else{
			if (Enemy4_List.IsEmpty());
			else{
				for (POSITION pos1 = Enemy4_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					Enemy4* temp1 = (Enemy4*)Enemy4_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3, C1, C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 50));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								temp1->goto_die();
							}
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		if (hero2->bullet_list.IsEmpty()) return;
		if (Enemy4_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy4_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Enemy4* temp1 = (Enemy4*)Enemy4_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3, C1, C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 50));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						temp1->goto_die();
					}
				}
			}
		}
	}
}
void GameMessage::EnemyAttack5()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		if (hero->bullet_list.IsEmpty());
		else{
			if (Enemy5_List.IsEmpty());
			else{
				for (POSITION pos1 = Enemy5_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					Enemy5* temp1 = (Enemy5*)Enemy5_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3, C1, C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 50));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								temp1->goto_die();
							}
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		if (hero2->bullet_list.IsEmpty()) return;
		if (Enemy5_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy5_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Enemy5* temp1 = (Enemy5*)Enemy5_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3, C1, C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 50));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						temp1->goto_die();
					}
				}
			}
		}
	}
}
void GameMessage::BossAttack()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1, post2;
	if (hero != NULL){
		if (hero->bullet_list.IsEmpty());
		else{
			if (Boss_List.IsEmpty());
			else{
				for (POSITION pos1 = Boss_List.GetHeadPosition(); (post1 = pos1) != NULL;)
				{
					BOSS1* temp1 = (BOSS1*)Boss_List.GetNext(pos1);
					if (temp1->return_dead()) continue; //敌机已经死亡
					for (POSITION pos2 = hero->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
					{
						Bullet* temp2 = (Bullet*)hero->bullet_list.GetNext(pos2);
						int w1 = temp1->return_width(), h1 = temp1->return_height();
						int w2 = temp2->return_width(), h2 = temp2->return_height();
						int x1 = temp1->return_x(), y1 = temp1->return_y();
						int x2 = temp2->return_x(), y2 = temp2->return_y();
						CRect C1(x1, y1, x1 + w1, y1 + h1);
						CRect C2(x2, y2, x2 + w2, y2 + h2);
						CRect C3(0, 0, 0, 0);
						if (IntersectRect(C3,C1,C2))
						{
							temp1->life -= temp2->return_hurt();
							Explo_List.AddTail(new Explo(1, x2, y2 - 50));
							hero->bullet_list.RemoveAt(post2);
							delete temp2;
							if (temp1->life <= 0){
								hero->score += temp1->score;
								Explo_List.AddTail(new Explo(2, x1, y1));
								Explo_List.AddTail(new Explo(2, x1 + 100, y1));
								Explo_List.AddTail(new Explo(2, x1 + 50, y1 + 50));
								Explo_List.AddTail(new Explo(2, x1 + 100, y1 + 100));
								Explo_List.AddTail(new Explo(2, x1, y1 + 200));
								Explo_List.AddTail(new Explo(2, x1 + 200, y1));
								temp1->goto_die();
							}
						}
					}
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		if (hero2->bullet_list.IsEmpty()) return;
		if (Boss_List.IsEmpty()) return;
		for (POSITION pos1 = Boss_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			BOSS1* temp1 = (BOSS1*)Boss_List.GetNext(pos1);
			if (temp1->return_dead()) continue; //敌机已经死亡
			for (POSITION pos2 = hero2->bullet_list.GetHeadPosition(); (post2 = pos2) != NULL;)
			{
				Bullet* temp2 = (Bullet*)hero2->bullet_list.GetNext(pos2);
				int w1 = temp1->return_width(), h1 = temp1->return_height();
				int w2 = temp2->return_width(), h2 = temp2->return_height();
				int x1 = temp1->return_x(), y1 = temp1->return_y();
				int x2 = temp2->return_x(), y2 = temp2->return_y();
				CRect C1(x1, y1, x1 + w1, y1 + h1);
				CRect C2(x2, y2, x2 + w2, y2 + h2);
				CRect C3(0, 0, 0, 0);
				if (IntersectRect(C3,C1,C2))
				{
					temp1->life -= temp2->return_hurt();
					Explo_List.AddTail(new Explo(1, x2, y2 - 50));
					hero2->bullet_list.RemoveAt(post2);
					delete temp2;
					if (temp1->life <= 0){
						hero2->score += temp1->score;
						Explo_List.AddTail(new Explo(2, x1, y1));
						Explo_List.AddTail(new Explo(2, x1 + 100, y1));
						Explo_List.AddTail(new Explo(2, x1 + 50, y1 + 50));
						Explo_List.AddTail(new Explo(2, x1 + 100, y1 + 100));
						Explo_List.AddTail(new Explo(2, x1, y1 + 200));
						Explo_List.AddTail(new Explo(2, x1 + 200, y1));
						temp1->goto_die();
					}
				}
			}
		}
	}
}
//英雄收到攻击
void GameMessage::HeroAttack()
{
	if (is_stop) return; //暂停停止刷新
	if (step == 0) return;
	POSITION post1;
	if (hero != NULL){
		//进行一号敌机机群的判断
		int x1 = hero->return_x(), y1 = hero->return_y();
		int w1 = hero->return_width(), h1 = hero->return_width();
		if (Enemy_Bullet_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy_Bullet_List.GetHeadPosition();(post1 = pos1) != NULL;)
		{
			Bullet* temp = (Bullet*)Enemy_Bullet_List.GetNext(pos1);
			int x2 = temp->return_x(), y2 = temp->return_y();
			int w2 = temp->return_width(), h2 = temp->return_height();
			CRect C1(x1, y1, x1 + w1, y1 + h1);
			CRect C2(x2, y2, x2 + w2, y2 + h2);
			CRect C3(0, 0, 0, 0);
			if (IntersectRect(C3,C1,C2))
			{
				hero->life -= temp->return_hurt();
				Explo_List.AddTail(new Explo(2, x2, y2 + 30)); //添加爆炸
				Enemy_Bullet_List.RemoveAt(post1);
				delete temp;
				if (hero->life <= 0)
				{
					Hero_score = hero->score;
					hero = NULL;
					break;
				}
			}
		}
	}
	if (hero2 != NULL)
	{
		int x1 = hero2->return_x(), y1 = hero2->return_y();
		int w1 = hero2->return_width(), h1 = hero2->return_width();
		if (Enemy_Bullet_List.IsEmpty()) return;
		for (POSITION pos1 = Enemy_Bullet_List.GetHeadPosition(); (post1 = pos1) != NULL;)
		{
			Bullet* temp = (Bullet*)Enemy_Bullet_List.GetNext(pos1);
			int x2 = temp->return_x(), y2 = temp->return_y();
			int w2 = temp->return_width(), h2 = temp->return_height();
			CRect C1(x1, y1, x1 + w1, y1 + h1);
			CRect C2(x2, y2, x2 + w2, y2 + h2);
			CRect C3(0, 0, 0, 0);
			if (IntersectRect(C3,C1,C2))
			{
				hero2->life -= temp->return_hurt();
				Explo_List.AddTail(new Explo(2, x2, y2 + 30)); //添加爆炸
				Enemy_Bullet_List.RemoveAt(post1);
				delete temp;
				if (hero2->life <= 0)
				{
					Hero2_score = hero2->score;
					hero2 = NULL;
					break;
				}
			}
		}
	}
}
void GameMessage::ShowHeroLife(CDC* pDC)
{
	if (is_talking) return;
	CBitmap bmp;
	CDC memDC;
	bmp.LoadBitmap(2000 + Hero_Kind);
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	for (int x = 0, count = 0; count < Hero_Life; count++, x += 45)
		pDC->TransparentBlt(x, rect.Height() - 68, 30, 30, &memDC, 0, 0, 124, 97, RGB(238, 243, 250));
	CBitmap bmp2;
	CDC memDC2;
	bmp2.LoadBitmap(2000 + Hero2_Kind);
	memDC2.CreateCompatibleDC(NULL);
	memDC2.SelectObject(&bmp2);
	for (int x = 30, count = 0; count < Hero2_Life; count++, x += 45)
		pDC->TransparentBlt(rect.Width() - x, rect.Height() - 68, 30, 30, &memDC2, 0, 0, 124, 97, RGB(238, 243, 250));
}
//判断物理撞击
CRect GameMessage::rect(0, 0, 0, 0);
BackGround* GameMessage::background		 = NULL;
BackGround* GameMessage::boombackground  = NULL;		//大招背景图
BackGround* GameMessage::boombackground2 = NULL;		//大招背景图
Talking* GameMessage::talkground		 = NULL;
Hero* GameMessage::hero = NULL;
Hero* GameMessage::hero2 = NULL;
HeroS* GameMessage::L_Hero  = NULL;
HeroS* GameMessage::L_Hero2 = NULL;
CObList GameMessage::Explo_List;
CObList GameMessage::Word_List;
CObList GameMessage::Enemy1_List;				//敌机一号机群
CObList GameMessage::Enemy2_List;				//敌机二号机群
CObList GameMessage::Enemy3_List;				//敌机三号机群
CObList GameMessage::Enemy4_List;				//敌机四号机群
CObList GameMessage::Enemy5_List;				//敌机五号机群
CObList GameMessage::Boss_List;					//boss链表
CObList GameMessage::Enemy_Bullet_List;			//敌人子弹
CObList GameMessage::Things_List;				//物品链表
PersonState* GameMessage::state1 = NULL;		//创建一个状态窗口
PersonState* GameMessage::state2 = NULL;
int GameMessage::is_talking = 0;				//是否正在谈话
int GameMessage::talking_step = 1;				//谈话进行步骤
int GameMessage::Hero_Life = 0;
int GameMessage::Hero2_Life = 0;
int GameMessage::step = 0;
int GameMessage::boss_num = 0;
int GameMessage::_OK = 1;
int GameMessage::Hero_Kind = 1;
int GameMessage::Hero2_Kind = 3;
int GameMessage::Hero_score = 0;
int GameMessage::Hero2_score = 0;
int GameMessage::pre_step;
int GameMessage::next_step;
int GameMessage::Count_Num = 0;
void GameMessage::GameManage() //游戏进度的管理
{
	//RandomEnemy(step);
	if (step == -3)  //视角缓存
	{
		for (int count = 0; count < 10; count++)
		{
			int x = rand() % rect.Width();
			int y = rand() % rect.Height();
			Explo_List.AddTail(new Explo(2, x, y));
		}
		for (int count = 0; count < 10; count++)
		{
			int x = rand() % rect.Width();
			int y = rand() % rect.Height();
			Explo_List.AddTail(new Explo(1, x, y));
		}
		for (int count = 0; count < 3; count++)
		{
			int x = rand() % rect.Width();
			int y = rand() % rect.Height();
			Explo_List.AddTail(new Explo(3, x, y));
		}
		Count_Num++;
		if (Count_Num > 6){
			step = next_step;
			if (step == -1){
				step = -1;
				if (hero != NULL || hero2 != NULL)
					background = new BackGround(BackGroundW, 0);
				else
					background = new BackGround(BackGround00, 0);
			}
			Count_Num = 0;
		}
	}
	else if (step == -2)
	{
		if (boombackground == NULL){
			boombackground = new BackGround(BackGroundBB, -rect.Width(), 0, 1, 0, 100);
			boombackground2 = new BackGround(BackGroundB, -rect.Width() * 2, 0, 1, 0, 100);
		}
		GameStop(); //游戏暂停
		int pos_x = boombackground->return_x();
		if (pos_x >= rect.Width())
		{
			boombackground = NULL;
			boombackground2 = NULL;
			step = pre_step;
			GameStart();
			Big_Boom();
		}
	}
	else if (step == -1)
	{
		GameInit();									//初始化
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			step = 0;
			background = new BackGround(BackGround0, 0);
		}
	}
	else if (step == 0)						   //No start
	{
		if (background == NULL)
		{
			background = new BackGround(BackGround0, 0); //载入
		}
		if ((GetKeyState(VK_RETURN) & 0x8000) && _OK)
		{
			GameContrl contrl;
			contrl.DoModal();
			step = Game_Lv::Start_step;	  //游戏开始
			if (step == 7)
			{
				background = new BackGround(BackGroundF, 5);
				boss_num = 1;
				talking_step = 15;
			}
			if (step == 6)
			{
				background = new BackGround(BackGroundF, 5);
				talking_step = 12;
			}
			if (step == 5)
			{
				background = new BackGround(BackGround4, 5);
				boss_num = 1;
				talking_step = 10;
			}
			if (step == 4)
			{
				background = new BackGround(BackGround4, 5);
				boss_num = 2;
				talking_step = 7;
			}
			if (step == 3)
			{
				background = new BackGround(BackGround3, 5);
				talking_step = 7;
			}
			if (step == 2)
			{
				background = new BackGround(BackGround2, 5);
				boss_num = 1;
				talking_step = 4;
			}
			if (step == 1){
				background = new BackGround(BackGround1, 5);
				talking_step = 1;
			}
			Hero_Life = Game_Lv::Hero_num;	//英雄生命赋值
			Hero2_Life = Game_Lv::Hero2_num;//二号英雄生命赋值
		}
	}
	else if (step == 1)				        //第一关
	{
		if (hero != NULL && hero->score > 50000)
		{
			step = 2;
			background = new BackGround(BackGround2, 5);
			boss_num = 1;
		}
		else if (hero2 != NULL && hero2->score > 50000)
		{
			step = 2;
			background = new BackGround(BackGround2, 5);
			boss_num = 1;
		}
	}
	else if (step == 2)
	{
		if (Boss_List.IsEmpty() && boss_num == 0)
		{
			step = -3;
			next_step = 3;
			background = new BackGround(BackGround3, 5);
		}
	}
	else if (step == 3)
	{
		if (hero != NULL && hero->score > 130000)
		{
			step = 4;
			background = new BackGround(BackGround4, 5);
			boss_num = 2;
		}
		else if (hero2 != NULL && hero2->score > 130000)
		{
			step = 4;
			background = new BackGround(BackGround4, 5);
			boss_num = 2;
		}
	}
	else if (step == 4)
	{
		if (Boss_List.IsEmpty() && boss_num == 0)
		{
			step = -3;
			next_step = 5;
			boss_num = 1;
		}
	}
	else if (step == 5)
	{
		if (Boss_List.IsEmpty() && boss_num == 0)
		{
			step = -3;
			background = new BackGround(BackGroundF, 5);
			next_step = 6;
		}
	}
	else if (step == 6)
	{
		if (hero != NULL && hero->score > 200000)
		{
			step = 7;
			boss_num = 1;
		}
		else if (hero2 != NULL && hero2->score > 200000)
		{
			step = 7;
			boss_num = 1;
			Big_Boom();  //清屏
		}
	}
	else if (step == 7)
	{
		if (Boss_List.IsEmpty() && boss_num == 0)
		{
			step = -3;
			next_step = 8;
			boss_num = 1;
		}
	}
	else if (step == 8)
	{
		if (Boss_List.IsEmpty() && boss_num == 0)
		{
			boss_num = 1;
			step = -3;			//进入爆炸
			next_step = -1;
		}
	}
}
void GameMessage::TalkMessage()
{
	if (step == 1)					//到达第一关
	{
		if (talking_step <= 3)		//进行对话
		{
			is_talking = 1;			//正在对话模式
			GameStop();				//游戏暂停
			if (talking_step == 1 && talkground == NULL)
			{
				talkground = new Talking(talking_step);		//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)			//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 3) 
				{
					talkground = new Talking(talking_step); //加载对话图
				}
				if (talking_step == 4){ //跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
	else if (step == 2)
	{
		if (talking_step <= 6)
		{
			is_talking = 1;
			GameStop();
			if (talking_step == 4 && talkground == NULL)
			{
				talkground = new Talking(talking_step);		//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)			//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 6)
				{
					talkground = new Talking(talking_step); //加载对话图
				}
				if (talking_step == 7)
				{ //跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
	else if (step == 4)
	{
		if (talking_step <= 9)
		{
			is_talking = 1;
			GameStop();
			if (talking_step == 7 && talkground == NULL)
			{
				talkground = new Talking(talking_step);		//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)			//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 9)
				{
					talkground = new Talking(talking_step); //加载对话图
				}
				if (talking_step == 10){ //跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
	else if (step == 5)
	{
		if (talking_step <= 11)
		{
			is_talking = 1;
			GameStop();
			if (talking_step == 10 && talkground == NULL)
			{
				talkground = new Talking(talking_step);			//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)				//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 11)
				{
					talkground = new Talking(talking_step);		//加载对话图
				}
				if (talking_step == 12){						//跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
	else if (step == 6)
	{
		if (talking_step <= 14)
		{
			is_talking = 1;
			GameStop();
			if (talking_step == 12 && talkground == NULL)
			{
				talkground = new Talking(talking_step);			//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)				//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 14)
				{
					talkground = new Talking(talking_step);		//加载对话图
				}
				if (talking_step == 15){						//跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
	else if (step == 7)
	{
		if (talking_step <= 19)
		{
			is_talking = 1;
			GameStop();
			if (talking_step == 15 && talkground == NULL)
			{
				talkground = new Talking(talking_step);			//加载对话图
			}
			if (GetKeyState(VK_RETURN) & 0x8000)				//回车键，进行下一个对话
			{
				talking_step++;
				if (talking_step <= 19)
				{
					talkground = new Talking(talking_step);		//加载对话图
				}
				if (talking_step == 20){						//跳出对话
					is_talking = 0;
					talkground = NULL;
					GameStart();
				}
			}
		}
	}
}
void GameMessage::RandomEnemy(int lv)				//进行敌人的生成
{
	if (is_stop) return;
	if (lv <= 0) return;
	if (lv == 1) //关卡为1
	{
		while (true)
		{
			int t = Enemy1_List.GetCount();
			if (t > GameLevel::Lv1_e1) break;
			Enemy1_List.AddTail(new Enemy1());
		}
		while (true)
		{
			int t = Enemy2_List.GetCount();
			if (t > GameLevel::Lv1_e2) break;
			else  Enemy2_List.AddTail(new Enemy2());
		}
		if (Enemy3_List.IsEmpty())
		{
			int pos_y = rand() % rect.Height();
			for (int count = 0, pos_x = -50; count < GameLevel::Lv1_e3; pos_x -= 150, count++)
			{
				Enemy3_List.AddTail(new Enemy3(0,pos_x,pos_y,1,0));
			}
		}
		if (Enemy5_List.IsEmpty())
		{
			int t = rand() % 2;
			if (t == 1){
				Enemy5_List.AddTail(new Enemy5(1, 0, 0, 1, 1));
				Enemy5_List.AddTail(new Enemy5(2, rect.Width(), 0, -1, 1));
			}
		}
	}
	if (lv == 2) //BOSS出现
	{
		if (Boss_List.IsEmpty() && boss_num > 0)
		{
			boss_num -= 1;
			Boss_List.AddTail(new BOSS1(1, rect.Width() / 2 - 338, -219 - 30));
		}
		int t = rand() % 2;
		if (t == 1)
		{
			if (Enemy5_List.IsEmpty())
			{
				Enemy5_List.AddTail(new Enemy5(3,rect.Width() - 400, -200, 0, 1));
				Enemy5_List.AddTail(new Enemy5(3,200, -200, 0 ,1));
			}
		}
	}
	if (lv == 3) //第三关
	{
		while (true)
		{
			int t = Enemy1_List.GetCount();
			if (t > GameLevel::Lv3_e1) break;
			Enemy1_List.AddTail(new Enemy1());
		}
		while (true)
		{
			int t = Enemy2_List.GetCount();
			if (t > GameLevel::Lv3_e2) break;
			else  Enemy2_List.AddTail(new Enemy2());
		}
		if (Enemy3_List.IsEmpty())
		{
			int pos_y = rand() % rect.Height();
			for (int count = 0, pos_x = -50; count < GameLevel::Lv3_e3; pos_x -= 150, count++)
			{
				Enemy3_List.AddTail(new Enemy3(0, pos_x, pos_y, 1, 0));
			}
		}
		if (Enemy4_List.IsEmpty())
		{
			int t = rand() % 10;
			if (t == 5)
				for (int i = 0; i < rect.Width(); i += 250)
				{
					Enemy4_List.AddTail(new Enemy4(i,-200));
				}
		}
	}
	if (lv == 4)  //第四关
	{
		if (Boss_List.IsEmpty() && boss_num > 0)
		{
			boss_num -= 2;
			Boss_List.AddTail(new BOSS1(2, rect.Width() / 2 - 100 ,- 50));
			Boss_List.AddTail(new BOSS1(3, rect.Width() ,-200));
		}
	}
	if (lv == 5)
	{
		if (Boss_List.IsEmpty() && boss_num > 0)
		{
			boss_num -= 1;
			Boss_List.AddTail(new BOSS1(4, rect.Width() / 2 - 100, -50));
		}
	}
	if (lv == 6)
	{
		if (Boss_List.IsEmpty() && boss_num > 0)
		{
			boss_num = 0;
			Boss_List.AddTail(new BOSS1(boss_num, rect.Width() / 2 - 100, -50));
		}
		while (true)
		{
			int t = Enemy1_List.GetCount();
			if (t > GameLevel::Lv6_e1) break;
			Enemy1_List.AddTail(new Enemy1());
		}
		while (true)
		{
			int t = Enemy2_List.GetCount();
			if (t > GameLevel::Lv6_e2) break;
			else  Enemy2_List.AddTail(new Enemy2());
		}
		if (Enemy3_List.IsEmpty())
		{
			int pos_y = rand() % rect.Height();
			for (int count = 0, pos_x = -50; count < GameLevel::Lv6_e3; pos_x -= 150, count++)
			{
				Enemy3_List.AddTail(new Enemy3(0, pos_x, pos_y, 1, 0));
			}
		}
		if (Enemy4_List.IsEmpty())
		{
			int t = rand() % 5;
			if (t == 1)
			for (int i = 0; i < rect.Width(); i += 250)
			{
				Enemy4_List.AddTail(new Enemy4(i, -200));
			}
		}
		if (Enemy5_List.IsEmpty())
		{
			Enemy5_List.AddTail(new Enemy5(1, 0, 0, 1, 1));
			Enemy5_List.AddTail(new Enemy5(2, rect.Width(), 0, -1, 1));
		}
	}
	else if (lv == 7)
	{
		if (Enemy5_List.IsEmpty())
		{
			Enemy5_List.AddTail(new Enemy5(1, 0, 0, 1, 1));
			Enemy5_List.AddTail(new Enemy5(2, rect.Width(), 0, -1, 1));
		}
		if (boss_num > 0)
		{
			Boss_List.AddTail(new BOSS1(5, rect.Width() / 2 - 500, -400));
			boss_num--;
		}
	}
	else if (lv == 8)
	{
		if (boss_num > 0)
		{
			Boss_List.AddTail(new BOSS1(1, rect.Width() / 2 - 100, -200,-1,-1));
			Boss_List.AddTail(new BOSS1(2, rect.Width() / 2 - 200, -250,1,-1));
			Boss_List.AddTail(new BOSS1(3, rect.Width() / 2 - 300, -300,2,-1));
			Boss_List.AddTail(new BOSS1(5, rect.Width() / 2 - 500, -400));
			boss_num = 0;
		}
	}
}
void GameMessage::GameInit()
{
	hero = NULL;
	hero2 = NULL;
	is_talking = 0;
	Explo_List.RemoveAll();
	Word_List.RemoveAll();
	Enemy1_List.RemoveAll();
	Enemy2_List.RemoveAll();
	Enemy3_List.RemoveAll();
	Enemy4_List.RemoveAll();
	Enemy5_List.RemoveAll();
	Things_List.RemoveAll();
	Boss_List.RemoveAll();
	Enemy_Bullet_List.RemoveAll();
	state1 = NULL;
	state2 = NULL;
	Hero2_Life = 0;
	Hero_Life  = 0;
	boss_num   = 0;
	Hero2_Kind = 3;
	Hero_Kind = 1;
	Hero_score = 0;
	Hero2_score = 0;
	Count_Num = 0;
}
void GameMessage::Big_Boom() //爆炸函数
{
	if (hero == NULL || hero2 == NULL) return;
	int Sum_Score = 0;
	Sum_Score =
		Enemy1_List.GetCount() * AllScore::score_enemy1 +
		Enemy2_List.GetCount() * AllScore::score_enemy2 +
		Enemy3_List.GetCount() * AllScore::score_enemy3 +
		Enemy4_List.GetCount() * AllScore::score_enemy4 +
		Enemy5_List.GetCount() * AllScore::score_enemy5;
	hero->score  += Sum_Score/2;
	hero2->score += Sum_Score/2;
	GameMessage::Enemy1_List.RemoveAll();				//敌机一号机群
	GameMessage::Enemy2_List.RemoveAll();				//敌机二号机群
	GameMessage::Enemy3_List.RemoveAll();				//敌机三号机群
	GameMessage::Enemy4_List.RemoveAll();				//敌机三号机群
	GameMessage::Enemy5_List.RemoveAll();				//敌机三号机群
	GameMessage::Enemy_Bullet_List.RemoveAll();			//敌人子弹
	if (!Boss_List.IsEmpty())
	{
		POSITION post;
		for (POSITION pos = Boss_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			BOSS1* temp = (BOSS1*)Boss_List.GetNext(pos);
			temp->life -= AllHurt::hurt_cb;
			if (temp->life <= 0)
			{
				Boss_List.RemoveAt(post);
				delete temp;
			}
			if (temp->Lv == 4)
			{
				temp->life = 10000;
			}
		}
	}
	for (int count = 0; count < 50; count++)
	{
		int x = rand() % rect.Width();
		int y = rand() % rect.Height();
		Explo_List.AddTail(new Explo(2,x, y));
	}
	for (int count = 0; count < 50; count++)
	{
		int x = rand() % rect.Width();
		int y = rand() % rect.Height();
		Explo_List.AddTail(new Explo(1, x, y));
	}
	for (int count = 0; count < 5; count++)
	{
		int x = rand() % rect.Width();
		int y = rand() % rect.Height();
		Explo_List.AddTail(new Explo(3, x, y));
	}
}
//CObList GameMessage::Explo_List;				//爆炸链表
//CObList GameMessage::Enemy1_List;				//敌机一号机群
//CObList GameMessage::Enemy2_List;				//敌机二号机群
//CObList GameMessage::Enemy3_List;				//敌机三号机群
//CObList GameMessage::Boss_List;				//boss链表
//CObList GameMessage::Enemy_Bullet_List;		//敌人子弹
//英雄
int GameMessage::is_stop = 0;
void GameMessage::GameStop()
{
	POSITION post;
	is_stop = 1;
	if (!Enemy1_List.IsEmpty())
	{
		for (POSITION pos = Enemy1_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy1* temp = (Enemy1*)Enemy1_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Enemy2_List.IsEmpty())
	{
		for (POSITION pos = Enemy2_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy2* temp = (Enemy2*)Enemy2_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Enemy3_List.IsEmpty())
	{
		for (POSITION pos = Enemy3_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy3* temp = (Enemy3*)Enemy3_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Enemy4_List.IsEmpty())
	{
		for (POSITION pos = Enemy4_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy4* temp = (Enemy4*)Enemy4_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Enemy5_List.IsEmpty())
	{
		for (POSITION pos = Enemy5_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy5* temp = (Enemy5*)Enemy5_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Enemy_Bullet_List.IsEmpty())
	{
		for (POSITION pos = Enemy_Bullet_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Bullet* temp = (Bullet*)Enemy_Bullet_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	if (!Boss_List.IsEmpty())
	{
		for (POSITION pos = Boss_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			BOSS1* temp = (BOSS1*)Boss_List.GetNext(pos);
			temp->speed = 0;
		}
	}
	background->speed = 0;
}
void GameMessage::GameStart()
{
	POSITION post;
	is_stop = 0;
	if (!Enemy1_List.IsEmpty())
	{
		for (POSITION pos = Enemy1_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy1* temp = (Enemy1*)Enemy1_List.GetNext(pos);
			temp->speed = AllSpeed::speed_enemy1;
		}
	}
	if (!Enemy2_List.IsEmpty())
	{
		for (POSITION pos = Enemy2_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy2* temp = (Enemy2*)Enemy2_List.GetNext(pos);
			temp->speed = AllSpeed::speed_enemy2;
		}
	}
	if (!Enemy3_List.IsEmpty())
	{
		for (POSITION pos = Enemy3_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy3* temp = (Enemy3*)Enemy3_List.GetNext(pos);
			temp->speed = AllSpeed::speed_enemy3;
		}
	}
	if (!Enemy4_List.IsEmpty())
	{
		for (POSITION pos = Enemy4_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy4* temp = (Enemy4*)Enemy4_List.GetNext(pos);
			temp->speed = AllSpeed::speed_enemy4;
		}
	}
	if (!Enemy5_List.IsEmpty())
	{
		for (POSITION pos = Enemy5_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Enemy5* temp = (Enemy5*)Enemy5_List.GetNext(pos);
			temp->speed = AllSpeed::speed_enemy5;
		}
	}
	if (!Enemy_Bullet_List.IsEmpty())
	{
		for (POSITION pos = Enemy_Bullet_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			Bullet* temp = (Bullet*)Enemy_Bullet_List.GetNext(pos);
			temp->speed = AllSpeed::speed_b4;
		}
	}
	if (!Boss_List.IsEmpty())
	{
		for (POSITION pos = Boss_List.GetHeadPosition(); (post = pos) != NULL;)
		{
			BOSS1* temp = (BOSS1*)Boss_List.GetNext(pos);
			temp->speed = AllSpeed::speed_boss;
		}
	}
	background->speed = 5;
}
void GameMessage::GameToStop()
{
	if (hero == NULL && hero2 == NULL) return;
	if (GetKeyState(VK_F1) & 0x8000)
	{
		if (is_stop) is_stop = 0;
		else is_stop = 1;
	}
}
/*
	放大招的时候所有地方单位静止，子弹静止
*/
void GameMessage::GameCombine()
{
	if (hero == NULL || hero2 == NULL) return;
	int x1 = hero->return_x(), y1  = hero->return_y();
	int w1 = hero->return_width(), h1 = hero->return_height();
	int x2 = hero2->return_x(), y2  = hero2->return_y();
	int w2 = hero2->return_width(), h2 = hero2->return_height();
	CRect C1(x1, y1, x1 + w1, y1 + h1);
	CRect C2(x2, y2, x2 + w2, y2 + h2);
	CRect C3(0, 0, 0, 0);
	if (GetKeyState('I') & 0x8000){
		if (GetKeyState(VK_NUMPAD8) & 0x8000){
			if (IntersectRect(C3, C1, C2) && hero->bound_num > 0 && hero2->bound_num > 0)
			{
				hero ->bound_num--;
				hero2->bound_num--;
				if (step != -2)
					pre_step = step;
				step = -2;
			}
		}
	}
}
void GameMessage::PlaneHit()
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int w1 = 0, h1 = 0, w2 = 0, h2 = 0;
	CRect Rh1(0, 0, 0, 0);
	CRect Rh2(0, 0, 0, 0);
	if (hero != NULL){
		x1 = hero->return_x();y1 = hero->return_y();
		w1 = hero->return_width(); h1 = hero->return_height();
		Rh1.SetRect(x1, y1, x1 + w1, y1 + h1);
	}
	if (hero2 != NULL){
		x2 = hero2->return_x(), y2 = hero2->return_y();
		w2 = hero2->return_width(), h2 = hero2->return_height();
		Rh2.SetRect(x2, y2, x2 + w2, y2 + h2);
	}
	POSITION post;
	if (!Enemy1_List.IsEmpty())
	for (POSITION pos = Enemy1_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy1* temp = (Enemy1*)Enemy1_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(),h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero!= NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2!= NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (!Enemy2_List.IsEmpty())
	for (POSITION pos = Enemy2_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy2* temp = (Enemy2*)Enemy2_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (!Enemy3_List.IsEmpty())
	for (POSITION pos = Enemy3_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy3* temp = (Enemy3*)Enemy3_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (!Enemy4_List.IsEmpty())
	for (POSITION pos = Enemy4_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy4* temp = (Enemy4*)Enemy4_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (!Enemy5_List.IsEmpty())
	for (POSITION pos = Enemy5_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Enemy5* temp = (Enemy5*)Enemy5_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			Explo_List.AddTail(new Explo(2, x3 + 50, y3 + 50));
			Explo_List.AddTail(new Explo(2, x3 + 0, y3 + 50));
			Explo_List.AddTail(new Explo(2, x3 + 50, y3 + 0));
			Explo_List.AddTail(new Explo(2, x3 + 25, y3 + 25));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			Explo_List.AddTail(new Explo(2, x3, y3));
			Explo_List.AddTail(new Explo(2, x3 + 50, y3 + 50));
			Explo_List.AddTail(new Explo(2, x3 + 0, y3 + 50));
			Explo_List.AddTail(new Explo(2, x3 + 50, y3 + 0));
			Explo_List.AddTail(new Explo(2, x3 + 25, y3 + 25));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (!Boss_List.IsEmpty())
	for (POSITION pos = Boss_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		BOSS1* temp = (BOSS1*)Boss_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x1, y1));
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			Explo_List.AddTail(new Explo(2, x3, y3));
			hero2->life -= temp->return_hurt();
			Explo_List.AddTail(new Explo(2, x2, y2));
		}
	}
	if (hero != NULL)
	{
		Hero_score = hero->score;
		if (hero->life <= 0) hero = NULL;
	}
	if (hero2 != NULL)
	{
		Hero2_score = hero2->score;
		if (hero2->life <= 0) hero2 = NULL;
	}
}  //碰撞函数
void GameMessage::ShowThings(CDC* cDC)
{
	if (is_stop) return;		//暂停停止刷新
	if (step == 0) return;
	if (Things_List.IsEmpty()) return;
	POSITION post;
	for (POSITION pos = Things_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Things* temp = (Things*)Things_List.GetNext(pos);
		temp->move();		//物品
		temp->draw(cDC);	//画出物品
		if (temp->return_dead())
		{
			Things_List.RemoveAt(post);
			delete temp;
		}
	}
}
void GameMessage::ThingHit()
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int w1 = 0, h1 = 0, w2 = 0, h2 = 0;
	CRect Rh1(0, 0, 0, 0);
	CRect Rh2(0, 0, 0, 0);
	if (hero != NULL){
		x1 = hero->return_x(); y1 = hero->return_y();
		w1 = hero->return_width(); h1 = hero->return_height();
		Rh1.SetRect(x1, y1, x1 + w1, y1 + h1);
	}
	if (hero2 != NULL){
		x2 = hero2->return_x(), y2 = hero2->return_y();
		w2 = hero2->return_width(), h2 = hero2->return_height();
		Rh2.SetRect(x2, y2, x2 + w2, y2 + h2);
	}
	POSITION post;
	if (!Things_List.IsEmpty())
	for (POSITION pos = Things_List.GetHeadPosition(); (post = pos) != NULL;)
	{
		Things* temp = (Things*)Things_List.GetNext(pos);
		int x3 = temp->return_x(), y3 = temp->return_y();
		int w3 = temp->return_width(), h3 = temp->return_height();
		CRect Rh3(x3, y3, x3 + w3, y3 + h3);
		CRect Rh4;
		if (hero != NULL && IntersectRect(Rh4, Rh1, Rh3))	//与英雄1碰撞
		{
			temp->goto_die();
			int t = temp->Lv;
			if (t == 1) hero->B_Lv++;
			else if (t == 2) hero->score += temp->value;
			else if (t == 3) hero->life  += temp->value;
			else if (t == 4) hero->bullet_num += temp->value;
		}
		if (hero2 != NULL && IntersectRect(Rh4, Rh2, Rh3))	//与英雄2碰撞
		{
			temp->goto_die();
			int t = temp->Lv;
			if (t == 1) hero2->B_Lv++;
			else if (t == 2) hero2->score += temp->value;
			else if (t == 3) hero2->life += temp->value;
			else if (t == 4) hero2->bullet_num += temp->value;
		}
	}
}