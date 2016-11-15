
// vtkSDIDoc.h : CvtkSDIDoc ��Ľӿ�
//


#pragma once

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
class CvtkSDIDoc : public CDocument
{
protected: // �������л�����
	CvtkSDIDoc();
	DECLARE_DYNCREATE(CvtkSDIDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CvtkSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
	vtkSmartPointer<vtkImageData> m_pImageData;

	afx_msg void OnResample();
	afx_msg void OnFileSaveAs();
};
