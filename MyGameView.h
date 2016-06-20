
// MyGameView.h : CMyGameView 类的接口
//

#pragma once


class CMyGameView : public CView
{
protected: // 仅从序列化创建
	CMyGameView();
	DECLARE_DYNCREATE(CMyGameView)

// 特性
public:
	CMyGameDoc* GetDocument() const;
	CDC MemDC; //首先定义一个显示设备对象
	CRect m_client; //获取DC
	CBitmap MemBitmap; //位图对象


// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	//virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MyGameView.cpp 中的调试版本
inline CMyGameDoc* CMyGameView::GetDocument() const
   { return reinterpret_cast<CMyGameDoc*>(m_pDocument); }
#endif

