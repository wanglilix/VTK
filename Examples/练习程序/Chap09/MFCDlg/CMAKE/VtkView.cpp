// D:\VTK\Examples\Chap09\MFCDlg\CMAKE\VtkView.cpp : 实现文件
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


// CVtkView 消息处理程序
void CVtkView::PreSubclassWindow()//负责建立VTK可视化管线
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(rect);//CWND类成员函数
	m_Render = vtkSmartPointer<vtkRenderer>::New();
	m_RenderWindow= vtkSmartPointer<vtkRenderWindow>::New();

	m_RenderWindow->SetParentId(this->m_hWnd);
	m_RenderWindow->SetSize(rect.Width(),rect.Height());
	m_RenderWindow->AddRenderer(m_Render);

	if (m_RenderWindow->GetInteractor()== NULL)//如果第一次，没有添加交互器
	{
		vtkSmartPointer<vtkRenderWindowInteractor>RenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
		RenderWindowInteractor->Initialize();
	}

	m_ImagePlaneWidget = vtkSmartPointer< vtkImagePlaneWidget >::New();//交互部件处理

	m_ResliceCursor = vtkSmartPointer< vtkResliceCursor >::New();
	m_ResliceCursorRep = vtkSmartPointer< vtkResliceCursorThickLineRepresentation >::New();
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);

	m_ResliceCursorWidget = vtkSmartPointer< vtkResliceCursorWidget>::New();
	m_ResliceCursorWidget->SetInteractor(m_RenderWindow->GetInteractor());   //交互部件表达实体
	m_ResliceCursorWidget->SetDefaultRenderer(m_Render);  
	//m_ResliceCursorWidget->SetRepresentation(m_ResliceCursorRep);

	m_RenderWindow->Start();

	CStatic::PreSubclassWindow();
}


void CVtkView::OnPaint()//负责客户区内场景的渲染
{
	CPaintDC dc(this); 
	m_Render->Render();
}

void CVtkView::SetImageData(vtkSmartPointer<vtkImageData> ImageData)//输入数据的接口函数
{
	if (ImageData == NULL)
	{
		return;
	}
	m_ImageData = ImageData;
	SetupReslice();
}
void CVtkView::SetupReslice()    //设立切片
{
	if (m_ImageData == NULL) return;
	int dims[3];
	m_ImageData->GetDimensions(dims);

	////////////////////////////////////////////////////////////////////////
	//初始化vtkImagePlaneWidget
	m_ImagePlaneWidget->SetInput(m_ImageData); //输入数据
	m_ImagePlaneWidget->SetPlaneOrientation(m_Direction); //切片方向
	m_ImagePlaneWidget->SetSliceIndex(dims[m_Direction]/2); //设置当前方向默认的层号
	m_ImagePlaneWidget->On(); 
	m_ImagePlaneWidget->InteractionOn(); //开启交互部件 

	//////////////////////////////////////////////////////////////////////////
	m_ResliceCursor->SetCenter(m_ImageData->GetCenter()); //设置默认切分中心点
	m_ResliceCursor->SetImage(m_ImageData); //设置输入
	m_ResliceCursor->SetThickMode(0); //设置切片模式

	m_ResliceCursorRep->GetResliceCursorActor()->   //representation用于显示十字坐标轴   
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);  //设置关联ResliceCursor对象
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetReslicePlaneNormal(m_Direction);//设置切片方向

	m_ResliceCursorWidget->SetEnabled(1); //开启
	m_Render->ResetCamera(); 

	//////////////////////////////////////////////////////////////////////////
	double range[2]; //设置数据范围
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