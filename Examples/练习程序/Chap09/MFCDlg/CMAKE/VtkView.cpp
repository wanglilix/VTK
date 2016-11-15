// D:\VTK\Examples\Chap09\MFCDlg\CMAKE\VtkView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "D:\VTK\Examples\Chap09\MFCDlg\CMAKE\VtkView.h"


// CVtkView

IMPLEMENT_DYNAMIC(CVtkView, CStatic)

CVtkView::CVtkView()
{

}

CVtkView::~CVtkView()
{
}


BEGIN_MESSAGE_MAP(CVtkView, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVtkView ��Ϣ�������
void CVtkView::PreSubclassWindow()//������VTK���ӻ�����
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(rect);//CWND���Ա����
	m_Render = vtkSmartPointer<vtkRenderer>::New();
	m_RenderWindow= vtkSmartPointer<vtkRenderWindow>::New();

	m_RenderWindow->SetParentId(this->m_hWnd);
	m_RenderWindow->SetSize(rect.Width(),rect.Height());
	m_RenderWindow->AddRenderer(m_Render);

	if (m_RenderWindow->GetInteractor()== NULL)//�����һ�Σ�û����ӽ�����
	{
		vtkSmartPointer<vtkRenderWindowInteractor>RenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
		RenderWindowInteractor->Initialize();
	}

	m_ImagePlaneWidget = vtkSmartPointer< vtkImagePlaneWidget >::New();//������������

	m_ResliceCursor = vtkSmartPointer< vtkResliceCursor >::New();
	m_ResliceCursorRep = vtkSmartPointer< vtkResliceCursorThickLineRepresentation >::New();
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);

	m_ResliceCursorWidget = vtkSmartPointer< vtkResliceCursorWidget>::New();
	m_ResliceCursorWidget->SetInteractor(m_RenderWindow->GetInteractor());   //�����������ʵ��
	m_ResliceCursorWidget->SetDefaultRenderer(m_Render);  
	//m_ResliceCursorWidget->SetRepresentation(m_ResliceCursorRep);

	m_RenderWindow->Start();

	CStatic::PreSubclassWindow();
}


void CVtkView::OnPaint()//����ͻ����ڳ�������Ⱦ
{
	CPaintDC dc(this); 
	m_Render->Render();
}

void CVtkView::SetImageData(vtkSmartPointer<vtkImageData> ImageData)//�������ݵĽӿں���
{
	if (ImageData == NULL)
	{
		return;
	}
	m_ImageData = ImageData;
	SetupReslice();
}
void CVtkView::SetupReslice()    //������Ƭ
{
	if (m_ImageData == NULL) return;
	int dims[3];
	m_ImageData->GetDimensions(dims);

	////////////////////////////////////////////////////////////////////////
	//��ʼ��vtkImagePlaneWidget
	m_ImagePlaneWidget->SetInput(m_ImageData); //��������
	m_ImagePlaneWidget->SetPlaneOrientation(m_Direction); //��Ƭ����
	m_ImagePlaneWidget->SetSliceIndex(dims[m_Direction]/2); //���õ�ǰ����Ĭ�ϵĲ��
	m_ImagePlaneWidget->On(); 
	m_ImagePlaneWidget->InteractionOn(); //������������ 

	//////////////////////////////////////////////////////////////////////////
	m_ResliceCursor->SetCenter(m_ImageData->GetCenter()); //����Ĭ���з����ĵ�
	m_ResliceCursor->SetImage(m_ImageData); //��������
	m_ResliceCursor->SetThickMode(0); //������Ƭģʽ

	m_ResliceCursorRep->GetResliceCursorActor()->   //representation������ʾʮ��������   
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);  //���ù���ResliceCursor����
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetReslicePlaneNormal(m_Direction);//������Ƭ����

	m_ResliceCursorWidget->SetEnabled(1); //����
	m_Render->ResetCamera(); 

	//////////////////////////////////////////////////////////////////////////
	double range[2]; //�������ݷ�Χ
	m_ImageData->GetScalarRange(range); 
	m_ResliceCursorWidget->GetResliceCursorRepresentation()->
		SetWindowLevel(range[1]-range[0], (range[0]+range[1])/2.0); 
	m_ImagePlaneWidget->SetWindowLevel(range[1]-range[0], (range[0]+range[1])/2.0); 


}

void CVtkView::SetResliceCursor(vtkSmartPointer< vtkResliceCursor > cursor)
{
	m_ResliceCursor = cursor;
}
void CVtkView::Render()
{
	m_RenderWindow->Render();
}