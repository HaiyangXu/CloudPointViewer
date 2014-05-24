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

#ifndef CLOUDVIEW_H
#define CLOUDVIEW_H


#include <pcl/visualization/pcl_visualizer.h>
#include <QVTKWidget.h>
#include <vtkImageViewer.h>
/*
 *CloudViewerWidget is a PCLVisualizer viewer in QWidget ,it can be used like a QWidget in Qt.
 *
*/

class CloudViewerWidget : public QVTKWidget
{
    Q_OBJECT
public:
    explicit CloudViewerWidget(QWidget *parent = 0);
    pcl::visualization::PCLVisualizer * getVisuallizer();
    vtkImageViewer* getImageViewer();

	~CloudViewerWidget();
public slots:
    void addPointCloud (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud,
                   const std::string &id = "cloud", int viewport = 0);
    void setRenderMode(bool arg);

private:
    pcl::visualization::PCLVisualizer m_CloudVisualizer;
    vtkImageViewer *m_ImageViewer;
};

#endif // CLOUDVIEW_H
