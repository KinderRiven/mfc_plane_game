// GameSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MyGame.h"
#include "GameSetting.h"
#include "afxdialogex.h"
#include "GameLevel.h"
#include "AllLife.h"

// GameSetting 对话框

IMPLEMENT_DYNAMIC(GameSetting, CDialogEx)

GameSetting::GameSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(GameSetting::IDD, pParent)
{

}

GameSetting::~GameSetting()
{
}

void GameSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, E1);	//小火力敌机
	E1.SetRange(1, 20);
	E1.SetPos(5);
	DDX_Control(pDX, IDC_SLIDER2, E2);	//中火力敌机
	E2.SetRange(1, 10);
	E2.SetPos(3);
	DDX_Control(pDX, IDC_SLIDER3, E3);  //小自杀飞机
	E3.SetRange(1, 20);
	E3.SetPos(8);
	DDX_Control(pDX, IDC_SLIDER5, B1);
	B1.SetRange(1, 10);
	B1.SetPos(3);
	DDX_Control(pDX, IDC_SLIDER6, B2);
	B2.SetRange(1, 10);
	B2.SetPos(5);
	DDX_Control(pDX, IDC_SLIDER7, B3);
	B3.SetRange(1, 10);
	B3.SetPos(5);
	DDX_Control(pDX, IDC_SLIDER8, B4);
	B4.SetRange(1, 10);
	B4.SetPos(8);
	DDX_Control(pDX, IDC_SLIDER9, T);
	T.SetRange(1, 5);
	T.SetPos(3);
}


BEGIN_MESSAGE_MAP(GameSetting, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GameSetting::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, &GameSetting::OnNMCustomdrawSlider8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &GameSetting::OnNMCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, &GameSetting::OnNMCustomdrawSlider7)
	ON_BN_CLICKED(IDC_BUTTON4, &GameSetting::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &GameSetting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &GameSetting::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &GameSetting::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &GameSetting::OnBnClickedButton5)
END_MESSAGE_MAP()


// GameSetting 消息处理程序


void GameSetting::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void GameSetting::OnNMCustomdrawSlider8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void GameSetting::OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void GameSetting::OnNMCustomdrawSlider7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void GameSetting::OnBnClickedButton4()
{
	//static int Lv1_e1, Lv1_e2, Lv1_e3;
	//static int Lv3_e1, Lv3_e2, Lv3_e3;
	//static int Lv6_e1, Lv6_e2, Lv6_e3;
	// TODO:  在此添加控件通知处理程序代码
	//int AllLife::life_boss1 = 70000;
	//int AllLife::life_boss2 = 150000;
	//int AllLife::life_boss3 = 150000;
	//int AllLife::life_boss4 = 300000;
	//int AllLife::life_boss5 = 200000;
	int e1 = E1.GetPos(), e2 = E2.GetPos(), e3 = E3.GetPos();
	int b1 = B1.GetPos(), b2 = B2.GetPos(), b3 = E3.GetPos(), b4 = B4.GetPos();
	int  t = T.GetPos();
	GameLevel::Lv1_e1 = e2 / 2; GameLevel::Lv3_e1 = e2; GameLevel::Lv6_e1 = e2 + 2;
	GameLevel::Lv1_e2 = e1;	GameLevel::Lv3_e2 = e1 + 5; GameLevel::Lv6_e2 = e1 + 10;
	GameLevel::Lv1_e3 = e3;	GameLevel::Lv3_e3 = e3 + 5; GameLevel::Lv6_e3 = e3 + 10;
	AllLife::life_boss1 =  50000 + b1 * 10000;
	AllLife::life_boss2 = 120000 + b2 * 10000;
	AllLife::life_boss3 = 120000 + b3 * 10000;
	AllLife::life_boss4 = AllLife::life_boss2 + AllLife::life_boss3;
	AllLife::life_boss4 = 160000 + b4 * 15000;
	GameLevel::Thing_drop = (5 - t);
	CDialogEx::OnOK();
}


void GameSetting::OnBnClickedButton1()
{
	E1.SetPos(5); 
	E2.SetPos(1);
	E3.SetPos(5);
	B1.SetPos(2);
	B2.SetPos(3);
	B3.SetPos(3);
	B4.SetPos(5);
	T.SetPos(5);
	// TODO:  在此添加控件通知处理程序代码
}


void GameSetting::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	E1.SetPos(10);
	E2.SetPos(3);
	E3.SetPos(8);
	B1.SetPos(3);
	B2.SetPos(5);
	B3.SetPos(5);
	B4.SetPos(7);
	T.SetPos(4);
}


void GameSetting::OnBnClickedButton3()
{
	E1.SetPos(15);
	E2.SetPos(8);
	E3.SetPos(12);
	B1.SetPos(5);
	B2.SetPos(7);
	B3.SetPos(7);
	B4.SetPos(9);
	T.SetPos(2);
	// TODO:  在此添加控件通知处理程序代码
}


void GameSetting::OnBnClickedButton5()	
{
	E1.SetPos(20);
	E2.SetPos(10);
	E3.SetPos(20);
	B1.SetPos(10);
	B2.SetPos(10);
	B3.SetPos(10);
	B4.SetPos(10);
	T.SetPos(2);
	// TODO:  在此添加控件通知处理程序代码
}
