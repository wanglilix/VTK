#pragma once


// CResampleDialog �Ի���

class CResampleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CResampleDialog)

public:
	CResampleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CResampleDialog(int dx, int dy, int dz, float sx, float sy, float sz, CWnd* pParent = NULL); //ָ�����캯��
	virtual ~CResampleDialog();
	void CResampleDialog::UpdateControl();
// �Ի�������
	enum { IDD = IDD_Resample };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iDx ,m_iDy,m_iDz;
	float m_fSx,m_fSy,m_fSz;
	bool m_bChangeDim;
	bool m_bChangeSpace;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioSpace();
	afx_msg void OnBnClickedRadioDimension();
	afx_msg void OnEnChangeEditDx();
	afx_msg void OnEnChangeEditDy();
	afx_msg void OnEnChangeEditDz();
	afx_msg void OnEnChangeEditSx();
	afx_msg void OnEnChangeEditSy();
	afx_msg void OnEnChangeEditSz();
	afx_msg void OnBnClickedOk();
};
