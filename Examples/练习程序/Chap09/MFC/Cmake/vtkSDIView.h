
// vtkSDIView.h : CvtkSDIView 类的接口
//

#pragma once
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>

class CvtkSDIView : public CView
{
protected: // 仅从序列化创建
	CvtkSDIView();
	DECLARE_DYNCREATE(CvtkSDIView)

// 特性
public:
	CvtkSDIDoc* GetDocument() const;

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
	virtual ~CvtkSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	vtkSmartPointer<vtkImageViewer2> m_pImageViewer;
	vtkSmartPointer<vtkRenderWindowInteractor> m_pRenderWindowInteractor;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // vtkSDIView.cpp 中的调试版本
inline CvtkSDIDoc* CvtkSDIView::GetDocument() const
   { return reinterpret_cast<CvtkSDIDoc*>(m_pDocument); }
#endif

