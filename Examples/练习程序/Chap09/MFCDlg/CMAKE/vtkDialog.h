
// vtkDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CvtkDialogApp:
// �йش����ʵ�֣������ vtkDialog.cpp
//

class CvtkDialogApp : public CWinApp
{
public:
	CvtkDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CvtkDialogApp theApp;