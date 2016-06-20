#pragma once


// AboutMe 对话框

class AboutMe : public CDialogEx
{
	DECLARE_DYNAMIC(AboutMe)

public:
	AboutMe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutMe();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
