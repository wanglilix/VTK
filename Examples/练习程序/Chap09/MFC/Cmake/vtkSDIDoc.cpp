
// vtkSDIDoc.cpp : CvtkSDIDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
#include <vtkImageReader2Factory.h>//返回可用的读取类对象
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


// CvtkSDIDoc 构造/析构

CvtkSDIDoc::CvtkSDIDoc()
{
	m_pImageData = vtkSmartPointer<vtkImageData>::New();//初始化m_pImageData
	m_pImageData = NULL;
	// TODO: 在此添加一次性构造代码

}

CvtkSDIDoc::~CvtkSDIDoc()
{
}

BOOL CvtkSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CvtkSDIDoc 序列化

void CvtkSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CvtkSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CvtkSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CvtkSDIDoc 诊断

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


// CvtkSDIDoc 命令
void CvtkSDIDoc::OnFileOpen()//打开
{
	CString FilePathName;
	m_pImageData = NULL;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("ALL Files(*.*)|*.*||"),NULL);
	
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();

		vtkSmartPointer<vtkImageReader2Factory> readerFactory = vtkSmartPointer<vtkImageReader2Factory>::New();//factory对象
		vtkImageReader2 * reader = readerFactory->CreateImageReader2(FilePathName.GetBuffer(0));//readerFactory返回可用的读取类的对象
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
	m_pImageData->GetDimensions(dims);//获取维度信息

	double spaces[3];
	m_pImageData->GetSpacing(spaces);//获取间隔信息

	CResampleDialog dlg(dims[0], dims[1], dims[2], spaces[0], spaces[1], spaces[2]);//创建默认对话框
	if(dlg.DoModal() == IDOK)
	{
		//get the new dimension and space information
		int dx = dlg.m_iDx;
		int dy = dlg.m_iDy;
		int dz = dlg.m_iDz;

		float sx = dlg.m_fSx;
		float sy = dlg.m_fSy;
		float sz = dlg.m_fSz;

		vtkSmartPointer<vtkImageResample> resample = //vtk图片采样filter
			vtkSmartPointer<vtkImageResample>::New();

		resample->SetInput(m_pImageData);
		resample->SetAxisOutputSpacing(0, sx);
		resample->SetAxisOutputSpacing(1, sy);
		resample->SetAxisOutputSpacing(2, sz);
		resample->SetInterpolationModeToLinear();//线性
		resample->SetInterpolationModeToNearestNeighbor();//最近邻

		vtkSmartPointer<vtkImageCast> imageCast = //vtk类型转换filter
			vtkSmartPointer<vtkImageCast>::New();
		imageCast->SetInput(resample->GetOutput());
		imageCast->SetOutputScalarTypeToUnsignedChar();
		imageCast->Update();


		m_pImageData = NULL;
		m_pImageData = resample->GetOutput();
		UpdateAllViews(0);                     //Doc类通知视图view更新
	}


}


void CvtkSDIDoc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pImageData== NULL) return ;

	CString FilePathName;

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("All Files(*.*)|*.*||"),NULL);
	 if (dlg.DoModal() == IDOK)
	 {
		 FilePathName = dlg.GetPathName();
		  CString m_ImageFormat; 
		 m_ImageFormat = FilePathName.Right(FilePathName.GetLength()-FilePathName.ReverseFind('.')-1);//提取扩展名
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
