#pragma once


// Contrl 对话框
#include "resource.h"

class Contrl : public CDialogEx
{
	DECLARE_DYNAMIC(Contrl)

public:
	Contrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Contrl();
	CComboBox  Game_Step;
	CEdit Hero_Life;
	CEdit Hero_Bullet;
	CComboBox Hero_num;
	int game_step;
	int hero_life;
	int hero_bullet;
	int hero_num;

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit3();
};
