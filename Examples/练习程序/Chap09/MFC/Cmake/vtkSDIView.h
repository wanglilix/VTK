
// vtkSDIView.h : CvtkSDIView ��Ľӿ�
//

#pragma once
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>

class CvtkSDIView : public CView
{
protected: // �������л�����
	CvtkSDIView();
	DECLARE_DYNCREATE(CvtkSDIView)

// ����
public:
	CvtkSDIDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CvtkSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // vtkSDIView.cpp �еĵ��԰汾
inline CvtkSDIDoc* CvtkSDIView::GetDocument() const
   { return reinterpret_cast<CvtkSDIDoc*>(m_pDocument); }
#endif

