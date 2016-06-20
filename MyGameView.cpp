
// MyGameView.cpp : CMyGameView 类的实现
//
#include "stdafx.h"
#include "BackGround.h"
#include "GameMessage.h"
#include "Windows.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyGame.h"
#endif

#include "MyGameDoc.h"
#include "MyGameView.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyGameView

IMPLEMENT_DYNCREATE(CMyGameView, CView)

BEGIN_MESSAGE_MAP(CMyGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMyGameView 构造/析构

CMyGameView::CMyGameView()
{
	// TODO:  在此处添加构造代码

}

CMyGameView::~CMyGameView()
{
}

BOOL CMyGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);
	return CView::PreCreateWindow(cs);
}

// CMyGameView 绘制

void CMyGameView::OnDraw(CDC* /*pDC*/)
{
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMyGameView 打印

BOOL CMyGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMyGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMyGameView 诊断

#ifdef _DEBUG
void CMyGameView::AssertValid() const
{
	CView::AssertValid();
}

void CMyGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGameDoc* CMyGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGameDoc)));
	return (CMyGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyGameView 消息处理程序


void CMyGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	GetClientRect(&GameMessage::rect); //获取
	CView::OnTimer(nIDEvent);
	CClientDC DC(this);
	switch (nIDEvent)
	{
	case 0:
		GameMessage::ShowBackground(&MemDC);
		GameMessage::ShowHero(&MemDC);	     //进行英雄的绘制(包括英雄发出的子弹)
		GameMessage::ShowEnemy1(&MemDC);     //进行一号敌机的绘制
		GameMessage::ShowEnemy2(&MemDC);	 //进行二号敌机的绘制
		GameMessage::ShowEnemy3(&MemDC);	 //进行三号敌机的绘制
		GameMessage::ShowEnemy4(&MemDC);	 //进行四号敌机的绘制
		GameMessage::ShowEnemy5(&MemDC);	 //进行五号敌机的绘制
		GameMessage::ShowEnemyBoss(&MemDC);	 //Boss的绘制
		GameMessage::ShowExplo(&MemDC);		 //爆炸绘制
		GameMessage::ShowState(&MemDC);		 //状态栏绘制
		GameMessage::ShowWord(&MemDC);		 //文字绘制
		GameMessage::ShowEnemyBullet(&MemDC);//敌人子弹
		GameMessage::ShowHeroLife(&MemDC);	 //命
		GameMessage::ShowThings(&MemDC);	 //物品
		DC.BitBlt(0, 0, GameMessage::rect.Width(), GameMessage::rect.Height(), &MemDC, 0, 0, SRCCOPY);
		break;
	case 1:
		GameMessage::GameManage();		//游戏进度管理
		break;
	case 2:
		GameMessage::GetKeyAttack();		//获得攻击信息
		break;
	case 3:
		GameMessage::EnemyAttack1();		//进行攻击敌人的判定
		GameMessage::EnemyAttack2();		//进行攻击敌人的判定
		GameMessage::EnemyAttack3();		//进行攻击敌人的判定
		GameMessage::EnemyAttack4();
		GameMessage::EnemyAttack5();
		GameMessage::BossAttack();			//BOSS被攻击
		GameMessage::HeroAttack();			//英雄被攻击
		GameMessage::PlaneHit();			//碰撞
		GameMessage::ThingHit();			//碰撞
		break;
	case 4:
		GameMessage::GameToStop();			//游戏暂停
		break;
	case 5:
		GameMessage::RandomEnemy(GameMessage::step);
	case 6:
		GameMessage::GameCombine();
		GameMessage::TalkMessage();		//对话管理
	}
}
void CMyGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	GetClientRect(&GameMessage::rect);
	PlaySound(L"sound.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	srand((unsigned)time);
	SetTimer(0, 50, 0);		 //每间隔50ms发送一个数字0
	SetTimer(1, 50, 0);		 //每间隔50ms发送一个数字1
	SetTimer(2,120, 0);		 //每间隔80ms发送一个数字2
	SetTimer(3, 50, 0);		 //每间隔50ms发送一个数字3
	SetTimer(4, 120, 0);	 //每间隔50ms发送一个数字4
	SetTimer(5, 2000, 0);	 //每间隔50ms发送一个数字5
	SetTimer(6, 300, 0);	 //每间隔50ms发送一个数字5
	// TODO:  在此添加专用代码和/或调用基类
	if (MemDC.m_hDC == NULL)
	{
		MemDC.CreateCompatibleDC(NULL);
		CClientDC DC(this);
		CRect rect;
		this->GetClientRect(&rect);
		MemBitmap.CreateCompatibleBitmap(&DC, rect.Width() * 5, rect.Height() * 5);
		MemDC.SelectObject(&MemBitmap);
	}
}