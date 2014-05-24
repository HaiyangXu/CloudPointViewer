/*------------------------------------------------------------------------------------------*\
  
  
  
   by Haiyang Xu, 2013.
   
   
   
   This program is free software; permission is hereby granted to use, copy, modify,
   and distribute this source code, or portions thereof, for any purpose, without fee,
   subject to the restriction that the copyright notice may not be removed
   or altered from any source or altered source distribution.
   
   The software is released on an as-is basis and without any warranties of any kind.
   In particular, the software is not guaranteed to be fault-tolerant or free from failure.
   The author disclaims all warranties with regard to this software, any use,
   and any consequent failure, is purely the responsibility of the user.
   
   Copyright (C) 2010-2011 Haiyang Xu         findway.xu@gmail.com
\*------------------------------------------------------------------------------------------*/

#include "CloudView.h"
#include "vtkPNGReader.h"
CloudViewerWidget::CloudViewerWidget(QWidget *parent) :QVTKWidget(parent)
{
	m_ImageViewer=vtkImageViewer::New();
    //m_CloudVisualizer.setBackgroundColor (1.0,1.0,1.0);
    this->SetRenderWindow(m_CloudVisualizer.getRenderWindow());
//    this->SetRenderWindow (m_CloudVisualizer.getRenderWindow ());
}
void CloudViewerWidget::addPointCloud(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud, const std::string &id, int viewport)
{
    m_CloudVisualizer.addPointCloud(cloud,id,viewport);
}

pcl::visualization::PCLVisualizer * CloudViewerWidget::getVisuallizer()
{
    return &m_CloudVisualizer;
}
vtkImageViewer * CloudViewerWidget::getImageViewer ()
{
    return m_ImageViewer;
}

void CloudViewerWidget::setRenderMode (bool arg)
{
//    if(arg)
//    {
//        vtkImageData *image=vtkImageData::New ();
//        image->SetDimensions (512,512,1);
//        image->SetScalarTypeToUnsignedChar ();
//        image->SetNumberOfScalarComponents (1);
//        image->GetPointData ()->SetScalars ();
//        image->AllocateScalars ();
//        m_ImageViewer->SetInput (image);
//        this->SetRenderWindow (m_ImageViewer->GetRenderWindow ());

//    }
//    else this->SetRenderWindow (m_CloudVisualizer.getRenderWindow ());

}

CloudViewerWidget::~CloudViewerWidget()
{
    m_ImageViewer->Delete ();
}
