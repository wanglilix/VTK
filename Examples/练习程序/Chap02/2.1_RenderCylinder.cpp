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
// //   :/VTK/VTK�����������/Examples/Chap02/data/texture.jpg
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




//////////////////////////////////////////////////////////////////////////P30 ����ӳ��
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
// 	//�����ļ���data/texture.jpg
// int main(int argc, char* argv[])
// {
// 	if (argc < 2)
// 	{
// 		std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
// 		return EXIT_FAILURE;
// 	}
// 	vtkSmartPointer< vtkJPEGReader > reader = 
// 		vtkSmartPointer< vtkJPEGReader >::New();
// 	reader->SetFileName(argv[1]);                //��ͼ��
// 
// 	vtkSmartPointer< vtkTexture > texture = 
// 		vtkSmartPointer< vtkTexture >::New();
// 	texture->SetInputConnection( reader->GetOutputPort() );   //������  ������ͼ��
// 	texture->InterpolateOn();
// 
// 	vtkSmartPointer< vtkPlaneSource > plane = 
// 		vtkSmartPointer< vtkPlaneSource >::New();            //ƽ����״����
// 	vtkSmartPointer< vtkPolyDataMapper > mapper = 
// 		vtkSmartPointer< vtkPolyDataMapper >::New();
// 	mapper->SetInputConnection( plane->GetOutputPort() );		//������  ������״����
// 
// 	vtkSmartPointer< vtkActor > actor = 
// 		vtkSmartPointer< vtkActor >::New();                   //��Ա  ͨ��������������������
// 	actor->SetMapper( mapper );
// 	actor->SetTexture( texture );
// 
// 	vtkSmartPointer<vtkRenderer> renderer = 
// 		vtkSmartPointer<vtkRenderer>::New();				//��̨   �����Ա�뱳��
// 	renderer->AddActor( actor );
// 	renderer->SetBackground( 1.0, 1.0, 1.0);
// 	renderer->SetViewport(0,0,0.5,0.5);
// 
// 	vtkSmartPointer<vtkRenderWindow> renWin =				//�糡    �����̨ 
// 		vtkSmartPointer<vtkRenderWindow>::New();
// 	renWin->AddRenderer( renderer );
// 	renWin->SetSize( 640, 480 );
// 	renWin->Render();
// 	renWin->SetWindowName("TextureExample");
// 
// 	vtkSmartPointer<vtkRenderWindowInteractor> iren =			//����
// 		vtkSmartPointer<vtkRenderWindowInteractor>::New();
// 	iren->SetRenderWindow(renWin);
// 	iren->Initialize();
// 	iren->Start();
// 
// 	return EXIT_SUCCESS;
// }

//////////////////////////////////////////////////////////////////////////P36 ���ӻ�����
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
	//����Structured_Points���͵�VTK�ļ�
	vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();//������ָ�빦�ܸ��� 
	reader->SetFileName("D:/VTK/Examples/Chap02/data/head.vtk");
	
	//���ƶ������巨��ȡ��ֵ��
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0,500);

    //�����ɵĵ�ֵ�����ݽ���Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());//���þ�������

	/////////////////////////////////////////////////////////////////////���ӻ����߽���.���ݴ���ܵ�����

	//��Mapper��������Ϊ��Ⱦ���������
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);//��Ա�������	�����ǽӿ�����

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindowInteractor>iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);//���û�����ʽΪĬ��ģʽ

	renderer->AddActor(actor);    //��̨�����Ա
	renWin->AddRenderer(renderer);//�糡�����̨

	iren->SetRenderWindow(renWin);//���û�������

	//renderer->Render();//����RENDER���� Actor�յ���Ⱦ����


	iren->Initialize();
	iren->Start();


	return 0;



}








