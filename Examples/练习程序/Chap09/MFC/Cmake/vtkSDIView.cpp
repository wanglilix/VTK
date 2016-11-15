
// vtkSDIView.cpp : CvtkSDIView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CvtkSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkSDIView 构造/析构

CvtkSDIView::CvtkSDIView()
{
	// TODO: 在此处添加构造代码

}

CvtkSDIView::~CvtkSDIView()
{
}

BOOL CvtkSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CvtkSDIView 绘制

void CvtkSDIView::OnDraw(CDC* /*pDC*/)
{
	CvtkSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码

	m_pImageViewer->SetInput(pDoc->m_pImageData);
	m_pImageViewer->Render();
}


// CvtkSDIView 打印


void CvtkSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CvtkSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CvtkSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CvtkSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CvtkSDIView 诊断

#ifdef _DEBUG
void CvtkSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkSDIDoc* CvtkSDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkSDIDoc)));
	return (CvtkSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkSDIView 消息处理程序


int CvtkSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pImageViewer->SetParentId(GetSafeHwnd()); //将MFC窗口的句柄设置为vtkImageViewer2的父窗口ID

	m_pRenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	m_pImageViewer->SetupInteractor(m_pRenderWindowInteractor);//设置交互器
	m_pRenderWindowInteractor->Start();




	return 0;
}


void CvtkSDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);
	m_pImageViewer->SetSize(rect.Width(),rect.Height());//设置图片大小为窗口大小

}
