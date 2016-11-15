//////////////////////////////////////////////////////////////////////////
// #include <vtkSmartPointer.h>
// #include<vtkRenderWindow.h>
// #include <vtkRenderer.h>
// #include <vtkRenderWindowInteractor.h>
// #include <vtkInteractorStyleTrackballCamera.h>
// #include <vtkCylinderSource.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkActor.h>
// #include <vtkLight.h>
// #include <vtkCamera.h>
// 
// 
// // D:/VTK/Examples/Chap02/bin/Debug/2.1_RenderCylinder.exe D
// //   :/VTK/VTK进阶随书代码/Examples/Chap02/data/texture.jpg
// 
// int main()
// {
// 	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
// 	cylinder->SetHeight(3.0);
// 	cylinder->SetRadius(1.0);
// 	cylinder->SetResolution(10);
// 
// 	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
// 	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
// 
// 	vtkSmartPointer<vtkActor>cylinderActor = vtkSmartPointer<vtkActor>::New();
// 	cylinderActor->SetMapper(cylinderMapper);
// 
// 	vtkSmartPointer<vtkRenderer>renderer = vtkSmartPointer<vtkRenderer>::New();
// 	renderer->AddActor(cylinderActor);
// 	renderer->SetBackground(0.1,0.2,0.4);
// 
// // 	vtkSmartPointer<vtkLight>myLight = vtkSmartPointer<vtkLight>::New();
// // 	myLight->SetColor(0,1,0);
// // 	myLight->SetPosition(0,0,1);
// // 	myLight->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
// // 	renderer->AddLight(myLight);
// // 
// // 	vtkSmartPointer<vtkLight>myLight2 = vtkSmartPointer<vtkLight>::New();
// // 	myLight2->SetColor(0,0,1);	
// // 	myLight2->SetPosition(0,0,-1);
// // 	myLight2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
// // 	renderer->AddLight(myLight2);
// 
// 	vtkSmartPointer<vtkCamera>myCamera = vtkSmartPointer<vtkCamera>::New();
// 	myCamera->SetClippingRange(0.0475,2.3786);
// 	myCamera->SetFocalPoint(0.0573,-0.2134,-0.0523);
// 	myCamera->SetPosition(0.3245,-0.1139,-0.2932);
// 	myCamera->SetViewUp(-0.2234,0.9983,0.0345);
// 	renderer->SetActiveCamera(myCamera);
// 
// 
// 	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
// 	renWin->AddRenderer(renderer);
// 	renWin->SetSize(300,300);
// 
// 	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
// 	iren->SetRenderWindow(renWin);
// 
// 	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
// 	iren->SetInteractorStyle(style);
// 
// 	iren->Initialize();
// 	iren->Start();
// 
// 	return 0 ;
// 
// 	}




//////////////////////////////////////////////////////////////////////////P30 纹理映射
// #include <vtkSmartPointer.h>
// #include <vtkJPEGReader.h>
// #include <vtkTexture.h>
// #include <vtkPlaneSource.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkActor.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderer.h>
// #include <vtkRenderWindowInteractor.h>
// 
// 	//测试文件：data/texture.jpg
// int main(int argc, char* argv[])
// {
// 	if (argc < 2)
// 	{
// 		std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
// 		return EXIT_FAILURE;
// 	}
// 	vtkSmartPointer< vtkJPEGReader > reader = 
// 		vtkSmartPointer< vtkJPEGReader >::New();
// 	reader->SetFileName(argv[1]);                //读图器
// 
// 	vtkSmartPointer< vtkTexture > texture = 
// 		vtkSmartPointer< vtkTexture >::New();
// 	texture->SetInputConnection( reader->GetOutputPort() );   //纹理器  关联读图器
// 	texture->InterpolateOn();
// 
// 	vtkSmartPointer< vtkPlaneSource > plane = 
// 		vtkSmartPointer< vtkPlaneSource >::New();            //平面形状数据
// 	vtkSmartPointer< vtkPolyDataMapper > mapper = 
// 		vtkSmartPointer< vtkPolyDataMapper >::New();
// 	mapper->SetInputConnection( plane->GetOutputPort() );		//塑性器  关联形状数据
// 
// 	vtkSmartPointer< vtkActor > actor = 
// 		vtkSmartPointer< vtkActor >::New();                   //演员  通过塑性器和纹理器打造
// 	actor->SetMapper( mapper );
// 	actor->SetTexture( texture );
// 
// 	vtkSmartPointer<vtkRenderer> renderer = 
// 		vtkSmartPointer<vtkRenderer>::New();				//舞台   添加演员与背景
// 	renderer->AddActor( actor );
// 	renderer->SetBackground( 1.0, 1.0, 1.0);
// 	renderer->SetViewport(0,0,0.5,0.5);
// 
// 	vtkSmartPointer<vtkRenderWindow> renWin =				//剧场    添加舞台 
// 		vtkSmartPointer<vtkRenderWindow>::New();
// 	renWin->AddRenderer( renderer );
// 	renWin->SetSize( 640, 480 );
// 	renWin->Render();
// 	renWin->SetWindowName("TextureExample");
// 
// 	vtkSmartPointer<vtkRenderWindowInteractor> iren =			//互动
// 		vtkSmartPointer<vtkRenderWindowInteractor>::New();
// 	iren->SetRenderWindow(renWin);
// 	iren->Initialize();
// 	iren->Start();
// 
// 	return EXIT_SUCCESS;
// }

//////////////////////////////////////////////////////////////////////////P36 可视化管线
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int argc,char *argv[])
{
	//读入Structured_Points类型的VTK文件
	vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();//比智能指针功能更多 
	reader->SetFileName("D:/VTK/Examples/Chap02/data/head.vtk");
	
	//用移动立方体法提取等值面
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0,500);

    //将生成的等值面数据进行Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());//设置具体造型

	/////////////////////////////////////////////////////////////////////可视化管线结束.数据传输管道结束

	//把Mapper的输入作为渲染引擎的输入
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);//演员添加造型	不再是接口连接

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindowInteractor>iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);//设置互动方式为默认模式

	renderer->AddActor(actor);    //舞台添加演员
	renWin->AddRenderer(renderer);//剧场添加舞台

	iren->SetRenderWindow(renWin);//设置互动窗口

	//renderer->Render();//调用RENDER函数 Actor收到渲染请求


	iren->Initialize();
	iren->Start();


	return 0;



}








