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
#pragma once
#ifndef CLOUDDATA_H
#define CLOUDDATA_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "CloudView.h"
#include <QString>
#include <QThread>
#include "ImageViewWidget.h"
#include<QtGui/QTextEdit>
#include <QMutex>
#include <QFuture>
#include <QtConcurrentRun>
#include <QFutureWatcher>

class CloudControl:public QThread
{
    Q_OBJECT
public:
    CloudControl();
    CloudControl(QTextEdit *textEdit);
    void setFiles(QStringList fileList);
	void compute();
    void consoleCompute();
    void convertPointToPointCloud();
    void saveCloud(QString fileName);
    void cmvs();//compute dense point with cmvs
    void setPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud);
   // pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbCloudPtr;
    void startThreadLog(QTextEdit *textEdit);
    void saveCameraDistortionMat(QStringList matList);
    void saveCameraDistortionMat();//save the computed camera and distortion matrix
    void setViewCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud);
    void openCloud(QString cloudFileName);
    CloudViewerWidget *getCloudViewWidget();
    ImageViewWidget *getImageViewWidget();
    void showMatches(int pos);
	int readply(std::string cloudFileName );
//    void setImageMode(bool arg);
    void saveMatches();
//    cv::Ptr<MultiCameraPnP> getDistance() const
//    {
//        return distance;
//    }

    int filter(double radiusOrstd=10.0, int neighbor=1, int kind=0);// filter cloud point with RadiusOutlier or statistical removal

protected:
     void run();
private:
	void SfmLibrary();
//    cv::Ptr<MultiCameraPnP> distance;
	std::string filePath;
    QTextEdit *textEdit;
    CloudViewerWidget *cloudViewWidget;
    ImageViewWidget * imageViewWidget;
    QWidget *viewWidgetParent;
//    cv::Mat imagePair;
	QMutex mutexCloud;
	QFuture<int> re;
	QFutureWatcher<int> watcher;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered ;
signals:
    void cloudReady(pcl::PointCloud<pcl::PointXYZ>::Ptr);
    void cloudReady (int i);
    //void finished();  this signal already exists in QThread
	void cloudupdated();

public slots:
    void addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const std::string &id = "cloud", int viewport = 0);
    void addPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,const std::string &id = "cloud", int viewport = 0);
	void showReadyCloud(int i);
	void readyToAdd();
};

#endif // CLOUDDATA_H
