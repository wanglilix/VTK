
// vtkSDIView.cpp : CvtkSDIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "vtkSDI.h"
#endif

#include "vtkSDIDoc.h"
#include "vtkSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkSDIView

IMPLEMENT_DYNCREATE(CvtkSDIView, CView)

BEGIN_MESSAGE_MAP(CvtkSDIView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CvtkSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkSDIView ����/����

CvtkSDIView::CvtkSDIView()
{
	// TODO: �ڴ˴���ӹ������

}

CvtkSDIView::~CvtkSDIView()
{
}

BOOL CvtkSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CvtkSDIView ����

void CvtkSDIView::OnDraw(CDC* /*pDC*/)
{
	CvtkSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	m_pImageViewer->SetInput(pDoc->m_pImageData);
	m_pImageViewer->Render();
}


// CvtkSDIView ��ӡ


void CvtkSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CvtkSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CvtkSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CvtkSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CvtkSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CvtkSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CvtkSDIView ���

#ifdef _DEBUG
void CvtkSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkSDIDoc* CvtkSDIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkSDIDoc)));
	return (CvtkSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkSDIView ��Ϣ�������


int CvtkSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pImageViewer->SetParentId(GetSafeHwnd()); //��MFC���ڵľ������ΪvtkImageViewer2�ĸ�����ID

	m_pRenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	m_pImageViewer->SetupInteractor(m_pRenderWindowInteractor);//���ý�����
	m_pRenderWindowInteractor->Start();




	return 0;
}


void CvtkSDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(rect);
	m_pImageViewer->SetSize(rect.Width(),rect.Height());//����ͼƬ��СΪ���ڴ�С

}
