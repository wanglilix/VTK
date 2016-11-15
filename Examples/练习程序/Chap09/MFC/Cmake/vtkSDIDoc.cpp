
// vtkSDIDoc.cpp : CvtkSDIDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "vtkSDI.h"
#endif

#include "vtkSDIDoc.h"
#include "MainFrm.h"
#include "vtkSDIView.h"
#include <propkey.h>
#include <vtkJPEGReader.h>
#include "ResampleDialog.h"
#include "vtkImageResample.h"
#include "vtkImageCast.h"
#include <vtkImageReader2Factory.h>//���ؿ��õĶ�ȡ�����
#include "vtkImageReader2.h"
#include "vtkJPEGWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CvtkSDIDoc

IMPLEMENT_DYNCREATE(CvtkSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CvtkSDIDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CvtkSDIDoc::OnFileOpen)
	ON_COMMAND(ID_RESAMPLE, &CvtkSDIDoc::OnResample)
	ON_COMMAND(ID_FILE_SAVE_AS, &CvtkSDIDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CvtkSDIDoc ����/����

CvtkSDIDoc::CvtkSDIDoc()
{
	m_pImageData = vtkSmartPointer<vtkImageData>::New();//��ʼ��m_pImageData
	m_pImageData = NULL;
	// TODO: �ڴ����һ���Թ������

}

CvtkSDIDoc::~CvtkSDIDoc()
{
}

BOOL CvtkSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CvtkSDIDoc ���л�

void CvtkSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CvtkSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CvtkSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CvtkSDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CvtkSDIDoc ���

#ifdef _DEBUG
void CvtkSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvtkSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvtkSDIDoc ����
void CvtkSDIDoc::OnFileOpen()//��
{
	CString FilePathName;
	m_pImageData = NULL;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("ALL Files(*.*)|*.*||"),NULL);
	
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();

		vtkSmartPointer<vtkImageReader2Factory> readerFactory = vtkSmartPointer<vtkImageReader2Factory>::New();//factory����
		vtkImageReader2 * reader = readerFactory->CreateImageReader2(FilePathName.GetBuffer(0));//readerFactory���ؿ��õĶ�ȡ��Ķ���
		if (reader)
		{
			reader->SetFileName(FilePathName.GetBuffer(0));
			reader->Update();
			m_pImageData = reader->GetOutput();
			reader->Delete();

			UpdateAllViews(0);
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
	UpdateAllViews(0,0,0);
}

void CvtkSDIDoc::OnResample()
{
	if (m_pImageData==NULL) return;

	int dims[3];
	m_pImageData->GetDimensions(dims);//��ȡά����Ϣ

	double spaces[3];
	m_pImageData->GetSpacing(spaces);//��ȡ�����Ϣ

	CResampleDialog dlg(dims[0], dims[1], dims[2], spaces[0], spaces[1], spaces[2]);//����Ĭ�϶Ի���
	if(dlg.DoModal() == IDOK)
	{
		//get the new dimension and space information
		int dx = dlg.m_iDx;
		int dy = dlg.m_iDy;
		int dz = dlg.m_iDz;

		float sx = dlg.m_fSx;
		float sy = dlg.m_fSy;
		float sz = dlg.m_fSz;

		vtkSmartPointer<vtkImageResample> resample = //vtkͼƬ����filter
			vtkSmartPointer<vtkImageResample>::New();

		resample->SetInput(m_pImageData);
		resample->SetAxisOutputSpacing(0, sx);
		resample->SetAxisOutputSpacing(1, sy);
		resample->SetAxisOutputSpacing(2, sz);
		resample->SetInterpolationModeToLinear();//����
		resample->SetInterpolationModeToNearestNeighbor();//�����

		vtkSmartPointer<vtkImageCast> imageCast = //vtk����ת��filter
			vtkSmartPointer<vtkImageCast>::New();
		imageCast->SetInput(resample->GetOutput());
		imageCast->SetOutputScalarTypeToUnsignedChar();
		imageCast->Update();


		m_pImageData = NULL;
		m_pImageData = resample->GetOutput();
		UpdateAllViews(0);                     //Doc��֪ͨ��ͼview����
	}


}


void CvtkSDIDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_pImageData== NULL) return ;

	CString FilePathName;

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("All Files(*.*)|*.*||"),NULL);
	 if (dlg.DoModal() == IDOK)
	 {
		 FilePathName = dlg.GetPathName();
		  CString m_ImageFormat; 
		 m_ImageFormat = FilePathName.Right(FilePathName.GetLength()-FilePathName.ReverseFind('.')-1);//��ȡ��չ��
		 if (m_ImageFormat == "")
		 {
			 m_ImageFormat = "mhd";
		 }
		 if (m_ImageFormat.Compare("jpg") == 0)
		 {
			 vtkSmartPointer<vtkJPEGWriter> writer = vtkSmartPointer<vtkJPEGWriter>::New();
			 writer->SetFileName(FilePathName.GetBuffer(0));
			 writer->SetInput(m_pImageData);
			 writer->Write();
		 }
	 }
}
