
// vtkDialogDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "D:\VTK\Examples\Chap09\MFCDlg\CMAKE\VtkView.h"
#include "vtkView3D.h"
#include "afxcmn.h"
#include <map>

// CvtkDialogDlg �Ի���
class CvtkDialogDlg : public CDialogEx
{
// ����
public:
	CvtkDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VTKDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CVtkView m_AxialView;
	CVtkView m_SagittalView;
	CVtkView m_CoronalView;
    CvtkView3D m_3DView;
	CTreeCtrl m_ImageTree;
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	HTREEITEM m_ImageTreeRoot;
	std::map<CString, vtkSmartPointer<vtkImageData> > m_Images;

	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	afx_msg void OnTreeFileOpen();
};
