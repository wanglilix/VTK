// ResampleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "vtkSDI.h"
#include "ResampleDialog.h"
#include "afxdialogex.h"


// CResampleDialog 对话框

IMPLEMENT_DYNAMIC(CResampleDialog, CDialogEx)

CResampleDialog::CResampleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResampleDialog::IDD, pParent)
{
	m_iDx=0;
	m_iDy=0;
	m_iDz=0;
	m_fSx=0;
	m_fSy=0;
	m_fSz=0;

	m_bChangeDim= 1;
	m_bChangeSpace = 0;
}

CResampleDialog::CResampleDialog(int dx, int dy, int dz, float sx, float sy, float sz, CWnd* pParent )
	: CDialogEx(CResampleDialog::IDD, pParent) //指定构造函数
{
	m_iDx = dx;
	m_iDy = dy;
	m_iDz = dz;

	m_fSx = sx;
	m_fSy = sy;
	m_fSz = sz;

	m_bChangeDim = 1;
}

CResampleDialog::~CResampleDialog()
{
}

void CResampleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResampleDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_SPACE, &CResampleDialog::OnBnClickedRadioSpace)
	ON_BN_CLICKED(IDC_RADIO_DIMENSION, &CResampleDialog::OnBnClickedRadioDimension)
	ON_EN_CHANGE(IDC_EDIT_DX, &CResampleDialog::OnEnChangeEditDx)
	ON_EN_CHANGE(IDC_EDIT_DY, &CResampleDialog::OnEnChangeEditDy)
	ON_EN_CHANGE(IDC_EDIT_DZ, &CResampleDialog::OnEnChangeEditDz)
	ON_EN_CHANGE(IDC_EDIT_SX, &CResampleDialog::OnEnChangeEditSx)
	ON_EN_CHANGE(IDC_EDIT_SY, &CResampleDialog::OnEnChangeEditSy)
	ON_EN_CHANGE(IDC_EDIT_SZ, &CResampleDialog::OnEnChangeEditSz)
	ON_BN_CLICKED(IDOK, &CResampleDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CResampleDialog 消息处理程序


BOOL CResampleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	str.Format("%d", m_iDx);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);

	str.Format("%d", m_iDy);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);

	str.Format("%d", m_iDz);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);

	str.Format("%.3f", m_fSx);
	GetDlgItem(IDC_EDIT_SX)->SetWindowText(str);

	str.Format("%.3f", m_fSy);
	GetDlgItem(IDC_EDIT_SY)->SetWindowText(str);

	str.Format("%.3f", m_fSz);
	GetDlgItem(IDC_EDIT_SZ)->SetWindowText(str);

	((CButton*)GetDlgItem(IDC_RADIO_DIMENSION))->SetCheck(TRUE);
	
	UpdateControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResampleDialog::UpdateControl()
{
	if(m_bChangeDim)
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_SX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(TRUE);
	}

	if (m_iDx <= 1) 
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SX)->EnableWindow(FALSE);
	}

	if (m_iDy <= 1) 
	{
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(FALSE);
	}

	if (m_iDz <= 1) 
	{
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(FALSE);
	}
}

void CResampleDialog::OnBnClickedRadioSpace()
{
	// TODO: 在此添加控件通知处理程序代
	m_bChangeDim = 0;
	UpdateControl();
}


void CResampleDialog::OnBnClickedRadioDimension()
{
	m_bChangeDim = 1;
	UpdateControl();
	// TODO: 在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditDx()
{
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	int dx = atoi(str);

	float sx = m_fSx*m_iDx/dx;
	str.Format("%.3f", sx);
	GetDlgItem(IDC_EDIT_SX)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditDy()
{
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	int dy = atoi(str);

	float sy = m_fSy*m_iDy/dy;
	str.Format("%.3f", sy);
	GetDlgItem(IDC_EDIT_SY)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditDz()
{
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	int dz = atoi(str);

	float sz = m_fSz*m_iDz/dz;
	str.Format("%.3f", sz);
	GetDlgItem(IDC_EDIT_SZ)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditSx()
{
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SX)->GetWindowText(str);
	float sx = atof(str);

	int dx = m_fSx*m_iDx/sx;
	str.Format("%d", dx);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditSy()
{
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SY)->GetWindowText(str);
	float sy = atof(str);

	int dy = m_fSx*m_iDy/sy;
	str.Format("%d", dy);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnEnChangeEditSz()
{
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SZ)->GetWindowText(str);
	float sz = atof(str);

	int dz = m_fSx*m_iDz/sz;
	str.Format("%d", dz);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);
	// TODO:  在此添加控件通知处理程序代码
}


void CResampleDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;

	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	m_iDx = atoi(str);

	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	m_iDy = atoi(str);

	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	m_iDz = atoi(str);

	GetDlgItem(IDC_EDIT_SX)->GetWindowText(str);
	m_fSx = atof(str);

	GetDlgItem(IDC_EDIT_SY)->GetWindowText(str);
	m_fSy = atof(str);

	GetDlgItem(IDC_EDIT_SZ)->GetWindowText(str);
	m_fSz = atof(str);
	CDialogEx::OnOK();
}
