
// vtkDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vtkDialog.h"
#include "vtkDialogDlg.h"
#include "afxdialogex.h"
#include "vtkCommand.h"
#include "D:\VTK\Examples\Chap09\MFCDlg\CMAKE\VtkView.h"
#include "vtkView3D.h"
#include "vtkPlaneSource.h"
#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"
using std::make_pair;
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

//Command����
class vtkResliceCursorCallback : public vtkCommand 
{ 
public: 
	static vtkResliceCursorCallback *New() 
	{ return new vtkResliceCursorCallback; } 

	void Execute( vtkObject *caller, unsigned long /*ev*/, 
		void *callData ) 
	{ 
		vtkResliceCursorWidget *rcw = dynamic_cast< 
			vtkResliceCursorWidget * >(caller); 
		if (rcw) 
		{ 
			for (int i = 0; i < 3; i++) 
			{ 
				vtkPlaneSource *ps = static_cast< vtkPlaneSource * >( 
					view[i]->GetImagePlaneWidget()->GetPolyDataAlgorithm()); 

				ps->SetOrigin(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetOrigin());
				ps->SetPoint1(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint1());
				ps->SetPoint2(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint2());

				view[i]->GetImagePlaneWidget()->UpdatePlacement(); 
				view[i]->Render();
			} 

			view3D->Render();
		} 
		
	} 

	vtkResliceCursorCallback() {} 
	CVtkView *view[3];
	CvtkView3D *view3D;
	//CvtkView *view3D;
}; 




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CvtkDialogDlg �Ի���




CvtkDialogDlg::CvtkDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CvtkDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvtkDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AxialView, m_AxialView);
	DDX_Control(pDX, IDC_SagittalView, m_SagittalView);
	DDX_Control(pDX, IDC_CoronalView, m_CoronalView);
	DDX_Control(pDX, IDC_3DView, m_3DView);
	DDX_Control(pDX, IDC_TREE1, m_ImageTree);
}

BEGIN_MESSAGE_MAP(CvtkDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CvtkDialogDlg::OnNMRClickTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CvtkDialogDlg::OnNMClickTree1)
	ON_COMMAND(ID_FILE_OPEN, &CvtkDialogDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, &CvtkDialogDlg::OnFileClose)
	ON_COMMAND(ID_TREE_FILE_OPEN, &CvtkDialogDlg::OnTreeFileOpen)
END_MESSAGE_MAP()


// CvtkDialogDlg ��Ϣ�������

BOOL CvtkDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ʼ���ļ���
	m_ImageTreeRoot = m_ImageTree.InsertItem("Images", NULL, NULL);
	m_ImageTree.Expand(m_ImageTreeRoot,TVE_EXPAND); 

	m_AxialView.SetSliceDirection(0);
	m_AxialView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_AxialView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());

	m_SagittalView.SetSliceDirection(1);
	m_SagittalView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_SagittalView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());
	m_SagittalView.SetResliceCursor(m_AxialView.GetResliceCursor());

	m_CoronalView.SetSliceDirection(2);
	m_CoronalView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_CoronalView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());
	m_CoronalView.SetResliceCursor(m_AxialView.GetResliceCursor());


	vtkSmartPointer<vtkResliceCursorCallback> cbk = 
		vtkSmartPointer<vtkResliceCursorCallback>::New(); 
	cbk->view[0] = &m_AxialView;
	m_AxialView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk ); 

	cbk->view[1] = &m_SagittalView;
	m_SagittalView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk );

	cbk->view[2] = &m_CoronalView;
	m_CoronalView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk );

	cbk->view3D = &m_3DView;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CvtkDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CvtkDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CvtkDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CvtkDialogDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt ;//= point;
	GetCursorPos(&pt);
	CPoint ScreenPt = pt;     //Screen coordinates 
	m_ImageTree.ScreenToClient(&pt);      //coordinates in Client Window

	UINT uFlags;
	HTREEITEM hItem = m_ImageTree.HitTest(pt, &uFlags); //Get selected item
	if ((hItem == m_ImageTreeRoot) && (TVHT_ONITEM & uFlags))
	{
		m_ImageTree.SetFocus();
		m_ImageTree.Select(hItem,TVGN_CARET);
		CMenu PopMenu;
		PopMenu.LoadMenu(IDR_MENU_FILE);
		PopMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,ScreenPt.x,ScreenPt.y,this);  
	}

	*pResult = 0;

}


void CvtkDialogDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint pt ;//= point;
	GetCursorPos(&pt);
	CPoint ScreenPt = pt;     //Screen coordinates 
	m_ImageTree.ScreenToClient(&pt);      //coordinates in Client Window

	UINT uFlags;
	HTREEITEM hItem = m_ImageTree.HitTest(pt, &uFlags); //Get selected item

	if ((hItem  != NULL) && (TVHT_ONITEM & uFlags))
	{
		CString str = m_ImageTree.GetItemText(hItem);   
		m_CoronalView.SetImageData(m_Images[str]);
		m_SagittalView.SetImageData(m_Images[str]);
		m_AxialView.SetImageData(m_Images[str]);
		m_3DView.Invalidate(FALSE);
	}

	*pResult = 0;
}


void CvtkDialogDlg::OnFileOpen()
{
	// TODO: �ڴ���������������
	// TODO: Add your command handler code here
	
}


void CvtkDialogDlg::OnFileClose()
{
	// TODO: �ڴ���������������
}


void CvtkDialogDlg::OnTreeFileOpen()
{
	CString FilePathName;
	vtkSmartPointer<vtkImageData> image = NULL;

	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);

	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();

		// Read file
		vtkSmartPointer<vtkImageReader2Factory> readerFactory =
			vtkSmartPointer<vtkImageReader2Factory>::New();
		vtkImageReader2 * reader = readerFactory->CreateImageReader2(FilePathName.GetBuffer(0));
		if (reader)
		{
			reader->SetFileName(FilePathName.GetBuffer(0));
			reader->Update();

			image = reader->GetOutput();
			reader->Delete();

			m_Images.insert(make_pair(FilePathName, image));
			HTREEITEM node = m_ImageTree.InsertItem(FilePathName, m_ImageTreeRoot, NULL);
			m_ImageTree.Expand(m_ImageTreeRoot,TVE_EXPAND); 
			m_ImageTree.SetRedraw(TRUE);


			m_CoronalView.SetImageData(image);
			m_SagittalView.SetImageData(image);
			m_AxialView.SetImageData(image);
			m_3DView.Render();

		}
		else
		{
			AfxMessageBox("Image Format is not supported now!");
		}
	}
	else
	{
		return;
	}
	// TODO: �ڴ���������������
}
