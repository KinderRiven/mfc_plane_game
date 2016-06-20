#pragma once
#include "BackGround.h"
#include "Hero.h"
#include "PersonState.h"
#include "Contrl.h"
#include "Talking.h"
#include "HeroS.h"
class GameMessage
{
public:
	GameMessage();
	~GameMessage();
	static int is_talking;
	static void TalkMessage();
	static int talking_step;
	static int _OK;
	static int pre_step;
	static int next_step;
	static int is_stop;
	static int Hero_score;
	static int Hero2_score;
	static int Count_Num;					//游戏视角缓存计数器
	static int step;						//游戏进度
	static int boss_num;					//boss的数量
	static int Hero_Kind;					//英雄种类
	static int Hero2_Kind;
	static void RandomEnemy(int lv);		//进行敌人的生成
	static int Hero_Life;					//英雄总命数
	static int Hero2_Life;					//英雄总命数
	static Hero* hero;						//拥有一个英雄
	static Hero* hero2;					   //拥有2个英雄
	static HeroS* L_Hero;					//英雄的小弟
	static HeroS* L_Hero2;					//英雄的小弟
	static PersonState* state1;				//第一个英雄状态窗口
	static PersonState* state2;
	static CRect rect;						//窗口
	static CObList Enemy1_List;				//敌机一号机群
	static CObList Enemy2_List;				//敌机二号机群
	static CObList Enemy3_List;				//敌机三号机群
	static CObList Enemy4_List;				//敌机四号机群
	static CObList Enemy5_List;				//敌机五号机群
	static CObList Boss_List;				//BOSS链表
	static CObList Explo_List;				//爆炸特效
	static CObList Word_List;				//文字
	static CObList Enemy_Bullet_List;		//敌人子弹的链表
	static CObList Things_List;				//物品链表		   
	static void ShowBackground(CDC* cDC);	//背景绘制函数
	static BackGround* background;			//一个背景图
	static BackGround* boombackground;		//大招背景图
	static BackGround* boombackground2;		//大招背景图
	static Talking* talkground;		//大招背景图
	static void GetKeyAttack();				//获得英雄攻击消息
	static void ShowHero(CDC* cDC);			//英雄绘制函数
	static void ShowHeroLife(CDC* cDC);		//显示英雄命数
	static void ShowEnemy1(CDC* cDC);		//敌机一号的绘制
	static void ShowEnemy2(CDC* cDC);		//敌机二号的绘制
	static void ShowEnemy3(CDC* cDC);		//敌机三号的绘制
	static void ShowEnemy4(CDC* cDC);		//敌机四号的绘制
	static void ShowEnemy5(CDC* cDC);		//敌机五号的绘制
	static void ShowEnemyBoss(CDC* cDC);	//BOss的绘制
	static void ShowExplo(CDC* cDC);		//爆照的绘制
	static void ShowWord(CDC* cDC);			//文字的绘制
	static void ShowEnemyBullet(CDC* cDC);	//敌机子弹绘制
	static void ShowState(CDC* cDC);		//状态窗口的绘制
	static void ShowThings(CDC* cDC);		//物品绘制
	static void EnemyAttack1();				//进行攻击的判断
	static void EnemyAttack2();				//进行攻击的判断
	static void EnemyAttack3();				//进行攻击的判断
	static void EnemyAttack4();
	static void EnemyAttack5();
	static void BossAttack();				//BOOS被攻击
	static void HeroAttack();				//英雄被攻击判断
	static void GameInit();					//游戏初始化
	static void Big_Boom();					//合体大爆炸
	static void GameManage();				//游戏进度的管理
	static void GameStop();					//游戏速度的停止管理
	static void GameStart();				//游戏速度回升
	static void GameToStop();				//暂停游戏
	static void GameCombine();				//合体技能
	static void PlaneHit();					//战机碰撞函数
	static void ThingHit();					//英雄吃物品函数
};

