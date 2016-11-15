#pragma once
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImagePlaneWidget.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursor.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkImageData.h"



// CVtkView

class CVtkView : public CStatic
{
	DECLARE_DYNAMIC(CVtkView)

public:
	CVtkView();
	void SetSliceDirection(int dir) {m_Direction = dir;}
	vtkSmartPointer< vtkImagePlaneWidget > GetImagePlaneWidget() {return m_ImagePlaneWidget;}
	vtkSmartPointer< vtkResliceCursorWidget >    GetResliceCursorWidget() {return m_ResliceCursorWidget;}

	vtkSmartPointer< vtkResliceCursor > GetResliceCursor() {return m_ResliceCursor;}
	void SetResliceCursor(vtkSmartPointer< vtkResliceCursor > cursor);
	void Render();
	//void SetResliceCursor(vtkSmartPointer< vtkResliceCursor >);
	virtual ~CVtkView();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnPaint();

	void SetImageData(vtkSmartPointer<vtkImageData>);
	void SetupReslice();
	vtkSmartPointer<vtkRenderer> m_Render;
	vtkSmartPointer<vtkRenderWindow> m_RenderWindow;

	vtkSmartPointer< vtkImagePlaneWidget >   m_ImagePlaneWidget;
	vtkSmartPointer< vtkResliceCursorWidget> m_ResliceCursorWidget;
	vtkSmartPointer< vtkResliceCursor >      m_ResliceCursor;
	vtkSmartPointer< vtkResliceCursorThickLineRepresentation > m_ResliceCursorRep;

	vtkSmartPointer<vtkImageData> m_ImageData;
	int m_Direction;

};


