#pragma once
#include "afxcmn.h"


// GameSetting 对话框

class GameSetting : public CDialogEx
{
	DECLARE_DYNAMIC(GameSetting)

public:
	GameSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GameSetting();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl E1;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl E2;
	CSliderCtrl E3;
	CSliderCtrl E4;
	CSliderCtrl B1;
	afx_msg void OnNMCustomdrawSlider8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl B2;
	CSliderCtrl B3;
	CSliderCtrl B4;
	afx_msg void OnNMCustomdrawSlider7(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl T;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
