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
#include "CloudControl.h"
//#include "Common.h"
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
//#include<opencv2\gpu\gpu.hpp>
#include <QDebug>
#include <QDirectStream.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <QProcess>
#include <QProgressDialog>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <QApplication>
CloudControl::CloudControl()
{

    rgbCloudPtr=pcl::PointCloud<pcl::PointXYZRGB>::Ptr( new pcl::PointCloud<pcl::PointXYZRGB>());
    cloud_filtered=pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>());
    //viewWidgetParent=new QWidget();
    //cloudViewWidget=new CloudViewerWidget(viewWidgetParent);
    //imageViewWidget=new ImageViewWidget(viewWidgetParent);

    //QObject::connect(this,SIGNAL(cloudReady(int)),this,SLOT(showReadyCloud(int)));//connect the signal and slot
}

CloudControl::CloudControl(QTextEdit* textEdit)
{
    this->textEdit=textEdit;
    viewWidgetParent=new QWidget();
    cloudViewWidget=new CloudViewerWidget(viewWidgetParent);
    imageViewWidget=new ImageViewWidget(viewWidgetParent);

    rgbCloudPtr=pcl::PointCloud<pcl::PointXYZRGB>::Ptr( new pcl::PointCloud<pcl::PointXYZRGB>());
    cloud_filtered=pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>());
    QDirectStream qout(std::cout/*, textEdit*/);//relocate cout to my log file ,in order to receive information from SFMLibrary
    QObject::connect(&qout,SIGNAL(textReady(QString)),textEdit,SLOT(append(QString))); //connect the QDirectStream textReady to QTextEdit'append.
	QObject::connect(this,SIGNAL(cloudReady(int)),this,SLOT(showReadyCloud(int)));//connect the signal and slot
}

//extern std::vector<cv::Mat> images;
//extern std::vector<std::string> images_names;
//extern std::string path;

void CloudControl::setFiles(QStringList fileList)
{
    //filePath=std::string(QFileList fileList);
    //double downscale_factor = 1.0; // downscale the input image
    //open_imgs_dir(QFileList fileList,images,images_names,downscale_factor);
//    if(!fileList.empty())
//		{

//			filePath=QFileInfo(*fileList.begin()).path().toStdString();
//			path=filePath;
//	}
//    QList<QString>::Iterator file=fileList.begin();
//    while( file!=fileList.end())
//    {
//        QFileInfo info(*file);
//        images.push_back(cv::imread((*file).toStdString()));
//        images_names.push_back(info.fileName().toStdString());
//        file++;
//    }


//	if(images.size() == 0)
//	{
//        std::cout << "can't get image files" << std::endl;
//		return ;
//	}

}


void CloudControl::SfmLibrary()
{	std::cout << "Step into CreatSfm() function" << std::endl;
//    if(!filePath.empty()&&distance.empty())
//	{
////        qDebug()<<"Create MultiCameraPnp";
//        std::cout<<"Create MultiCameraPnP Object successfully !";
//		distance=new MultiCameraPnP(images,images_names,filePath);
//		distance->use_gpu = (cv::gpu::getCudaEnabledDeviceCount() > 0);
//        distance->use_rich_features=1;//use RICH features
//		//cv::Ptr<CloudListener> listener = new CloudListener; //with ref-count
//        //distance->attach(listener);
//	}


}

void CloudControl::startThreadLog(QTextEdit *textEdit)
{
    this->textEdit=textEdit;
   // this->textEdit->setTextFormat(Qt::LogText);
    start(); //start
}

void CloudControl::compute()
{
//    QDirectStream qout(std::cout/*, textEdit*/);//relocate cout to my log file ,in order to receive information from SFMLibrary
//    QObject::connect(&qout,SIGNAL(textReady(QString)),textEdit,SLOT(append(QString))); //connect the QDirectStream textReady to QTextEdit'append.
//    SfmLibrary();
//	if(!distance.empty())
//    {
//        distance->RecoverDepthFromImages();
//		point=distance->getPointCloud();
//        rgb=distance->getPointCloudRGB ();
//        convertPointToPointCloud();
//	}

}

void CloudControl::consoleCompute()
{
//    SfmLibrary();
//    if(!distance.empty())
//    {
//        distance->RecoverDepthFromImages();
//        point=distance->getPointCloud();
//        rgb=distance->getPointCloudRGB ();
//        convertPointToPointCloud();
//    }
}

void CloudControl::run()
{
    compute();
    //setViewCloud (cloudPtr);  this can cause thread problems
	emit cloudReady(1);
}


void CloudControl::convertPointToPointCloud()
{
//    std::vector<cv::Point3d>::iterator itPoint=point.begin();
//    std::vector<cv::Vec3b>::iterator itRGB=rgb.begin();
//    pcl::PointXYZRGB rgbPoint;
//    cv::Vec3b color;

//    while(itPoint!=point.end())
//    {
//        rgbPoint.x=itPoint->x;
//        rgbPoint.y=itPoint->y;
//        rgbPoint.z=itPoint->z;

//        color=*itRGB;
//        rgbPoint.r=color[0];
//        rgbPoint.g=color[1];
//        rgbPoint.b=color[2];

//        rgbCloudPtr->push_back(rgbPoint);

//        itPoint++;
//        itRGB++;
//    }
}

void CloudControl::saveCloud(QString fileName)
{

    pcl::PLYWriter writer;
	writer.write(fileName.toStdString(),*rgbCloudPtr);
	emit finished();
    /*QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Point Cloud (*.ply)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec())
    {
        QStringList fileList= dialog.selectedFiles();
        QString fileName=fileList.last();
        QFileInfo info(fileName);
        if(info.suffix()=="ply")
        {
            writer.write(fileName.toStdString(),*rgbCloudPtr);
        }
        else
        {
            fileName.append(".ply");
            writer.write(fileName.toStdString(),*rgbCloudPtr);
        }
    }*/
}

void CloudControl::cmvs()
{
    QString path;
    QDirectStream qout(std::cout/*, textEdit*/);//relocate cout to my log file ,in order to receive information
    QObject::connect(&qout,SIGNAL(textReady(QString)),textEdit,SLOT(append(QString))); //connect the QDirectStream textReady to QTextEdit'append.
//    if(!distance.empty())
//    {
//        // creat the directory structure to run cmvs.exe
//        std::cout<<"creat the directory structure to run pmvs2.exe"<<std::endl;
//        QFileDialog dialog;
//        dialog.setFileMode(QFileDialog::AnyFile);
//        dialog.setNameFilter(tr("CMVS (*.CMVS)"));
//        dialog.setAcceptMode(QFileDialog::AcceptSave);
//        if(dialog.exec())
//        {
//            QStringList fileList= dialog.selectedFiles();
//            QString filePath_Name=fileList.last();
//            path= filePath_Name;
//            QFileInfo info(filePath_Name);
//            QDir dir;
//            dir.mkpath(info.filePath());
//            dir.cd(info.filePath());
//            dir.cd(info.fileName());
//            dir.mkdir("txt");
//            dir.mkdir("models");
//            dir.mkdir("visualize");
//        }

//        // prepare the images  to run cmvs.exe
//        std::cout<<"prepare the images  to run pmvs2.exe"<<std::endl;
//        std::vector<cv::Mat>::const_iterator imageIt=images.begin();
//        int imageNum=0;
//        QString imagePath=path+"/visualize/";
//        QString imageName;

//        while(imageIt!=images.end())
//        {
//            {
//                 QTextStream nameStream(&imageName);
//                 nameStream.setFieldWidth(8);
//                 nameStream.setPadChar('0');
//                 nameStream<<imageNum;
//                 nameStream.setFieldWidth(0);
//                 nameStream<<".jpg";
//            }

//            //cv::imwrite((imagePath+imageName).toStdString(),*imageIt);
//            imageIt++;
//            imageNum++;
//            imageName.clear();
//        }
//        // prepare the camera matrix .txt files  to run cmvs.exe
//        std::cout<<"prepare the camera matrix .txt files"<<std::endl;
//        QString txtPath=path+"/txt/";
//        int txtNum=0;
//        QString txtName;
//        //std::vector<cv::Matx34d> cameraVectors= distance->getCameras();
//        cv::Matx33d K=distance->getIntrinsic();
//       // std::vector<cv::Matx34d>::const_iterator cameraIt=cameraVectors.begin();
//        while(cameraIt!=cameraVectors.end())
//        {
//            {
//                 QTextStream nameStream(&txtName);
//                 nameStream.setFieldWidth(8);
//                 nameStream.setPadChar('0');
//                 nameStream<<txtNum;
//                 nameStream.setFieldWidth(0);
//                 nameStream<<".txt";
//            }
//            QFile txtFile(txtPath+txtName);
//            if(!txtFile.open(QIODevice::WriteOnly|QIODevice::Text))
//                break;
//            QTextStream out(&txtFile);
//            out<<"CONTOUR"<<'\n';
//            cv::Matx34d cameraMatrix=K*(*cameraIt);
//            out<<cameraMatrix(0,0)<<" "<<cameraMatrix(0,1)<<" "<<cameraMatrix(0,2)<<" "<<cameraMatrix(0,3)<<'\n';
//            out<<cameraMatrix(1,0)<<" "<<cameraMatrix(1,1)<<" "<<cameraMatrix(1,2)<<" "<<cameraMatrix(1,3)<<'\n';
//            out<<cameraMatrix(2,0)<<" "<<cameraMatrix(2,1)<<" "<<cameraMatrix(2,2)<<" "<<cameraMatrix(2,3)<<'\n';
//            txtFile.close();
//            txtNum++;
//            cameraIt++;
//            txtName.clear();
//        }

//        //prepare option file for pmvs2
//        std::cout<<"prepare option file for pmvs2"<<std::endl;
//        QFile optionFile(path+"/option.txt");
//        if(!optionFile.open(QIODevice::WriteOnly|QIODevice::Text))
//            ;
//        QTextStream out(&optionFile);
//        out<<"timages -1 0 "<<txtNum-1<<" oimages 0";
//        optionFile.close();



//        //execute pmvs2 to run dense reconstruction.
//        std::cout<<"execute pmvs2 to run dense reconstruction."<<std::endl;
//        QString cmvs="pmvs2.exe";
//        QStringList arguments;
//        arguments<<path+"/"<<"option.txt";
//        QProcess *cmvsProcess=new QProcess(this);
//        cmvsProcess->setReadChannelMode(QProcess::ForwardedChannels);//set the process to foward the output channel to the calling process.
//        cmvsProcess->start(cmvs,arguments);
//        if(cmvsProcess->error()==QProcess::FailedToStart)
//            std::cout<<"failed to run pmvs2 program, please make sure you have put the pmvs2 program in this program's root directory !";








//    }
}

void CloudControl::saveCameraDistortionMat(QStringList matList)
{


//    cv::Mat cameraMat;
//    cv::Mat cameraDistort;
//    cameraMat=(cv::Mat_<double>(3,3)<<
//               QString(matList[0]).toDouble(),QString(matList[1]).toDouble(),QString(matList[2]).toDouble(),
//               QString(matList[3]).toDouble(),QString(matList[4]).toDouble(),QString(matList[5]).toDouble(),
//               QString(matList[6]).toDouble(),QString(matList[7]).toDouble(),QString(matList[8]).toDouble()
//               );


//    cameraDistort=(cv::Mat_<double>(1,4)<<
//                   QString(matList[9]).toDouble(),QString(matList[10]).toDouble(),QString(matList[11]).toDouble(),QString(matList[12]).toDouble()
//                   );

//    cv::FileStorage fs;
//    fs.open(filePath+"\\out_camera_data.yml",cv::FileStorage::WRITE);

//    if(fs.isOpened())
//    {
//        fs<<"camera_matrix"<<cameraMat<<"distortion_coefficients"<<cameraDistort;
//        std::cout<<fs.elname<<"  FilePath:" <<filePath<<"Open \"out_camera_data.yml\" and Write Successfully ! "<<std::endl;
//    }else
//        std::cout<<fs.elname<<"  FilePath:" <<filePath<<"Failed to open \"out_camera_data.yml\" and Write ! "<<std::endl;

//    fs.release();
}

void CloudControl::saveCameraDistortionMat()
{
//    cv::FileStorage fs;
//    fs.open(filePath+"\\out_camera_data.yml",cv::FileStorage::WRITE);

//    if(fs.isOpened())
//    {
//        fs<<"camera_matrix"<<distance->getIntrinsic()<<"distortion_coefficients"<<distance->getDistortion();
//        std::cout<<fs.elname<<"  FilePath:" <<filePath<<"Open \"out_camera_data.yml\" and Write Successfully ! "<<std::endl;
//    }else
//        std::cout<<fs.elname<<"  FilePath:" <<filePath<<"Failed to open \"out_camera_data.yml\" and Write ! "<<std::endl;
//    fs.release();

}

void CloudControl::addPointCloud (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                                   const std::string &id, int viewport)
{
	cloudViewWidget->getVisuallizer()->removePointCloud();
    cloudViewWidget->getVisuallizer ()->addPointCloud(cloud,id,viewport);
    cloudViewWidget->getVisuallizer ()->resetCameraViewpoint (id);
}
void CloudControl::addPointCloud (pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,
                                   const std::string &id, int viewport)
{
	
	cloudViewWidget->getVisuallizer()->removePointCloud();
    cloudViewWidget->getVisuallizer ()->addPointCloud(cloud,id,viewport);
    cloudViewWidget->getVisuallizer ()->resetCameraViewpoint (id);
}

void CloudControl::showReadyCloud(int i)
{
    if(i==1)
        addPointCloud(rgbCloudPtr);
    else if(i==2)
        addPointCloud(cloud_filtered);
}
void CloudControl::setViewCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    addPointCloud(cloud);
}

CloudViewerWidget *CloudControl::getCloudViewWidget()
{
    imageViewWidget->setParent (viewWidgetParent); // QMainWindow's setCentralWidget() will make its old centralWidget  deleted . In order to perserve that old centralWidget , use setParent() to make the old central Widget remove from QMainWindow and have a parent.
    return cloudViewWidget;
}
ImageViewWidget *CloudControl::getImageViewWidget()
{
    cloudViewWidget->setParent (viewWidgetParent);
    return imageViewWidget;
}

void CloudControl::setPointCloud (pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud)
{
    rgbCloudPtr=cloud;
    setViewCloud (cloud);
}
//void CloudControl::setImageMode (bool arg)
//{
//    if(arg);
//}
void CloudControl::showMatches (int pos)
{

//    if(!distance.empty ())
//    {
    
//	if(distance->getMatchPair (pos,imagePair))
//	{
//		imagePair.type();
//		cv::cvtColor(imagePair,imagePair,CV_BGR2RGB);
//		QImage img= QImage((const unsigned char*)(imagePair.data),
//			   imagePair.cols,imagePair.rows,QImage::Format_RGB888);
//			// display on label

//        getImageViewWidget ()->setImage (img);
//		// resize the label to fit the image
//	   // getImageViewWidget ()->resize(img.size ());
//	}
//    }

}


int CloudControl::readply(std::string cloudFileName )
{
	pcl::PLYReader reader;

	QMutexLocker locker( &mutexCloud);
	reader.read(cloudFileName,*rgbCloudPtr);
	emit finished();
	return 1;

}

void CloudControl::saveMatches()
{
//    distance->saveMatchesToFile();
}

//kind =0 radius removal
//kind=1  statistical removal
int CloudControl::filter(double radiusOrstd, int neighbor,int kind)
{
    int flag=0;
    if(rgbCloudPtr->size()!=0)
    {
        if(kind==0)
        {
            pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> outrem;
            // build the filter
            outrem.setInputCloud(rgbCloudPtr);
            outrem.setRadiusSearch(radiusOrstd);
            outrem.setMinNeighborsInRadius (neighbor);
            // apply filter

            outrem.filter (*cloud_filtered);
            //addPointCloud(cloud_filtered); //show up
            rgbCloudPtr=cloud_filtered;
            emit cloudReady(2); //cloud_filtered
            flag=0;
        }
        else if (kind==1)
        {
            // Create the filtering object
              pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
              sor.setInputCloud (rgbCloudPtr);
              sor.setMeanK (neighbor);
              sor.setStddevMulThresh (radiusOrstd);

              sor.filter (*cloud_filtered);
              rgbCloudPtr=cloud_filtered;
              emit cloudReady(2); //cloud_filtered
              flag=0;

        }

    }
    else
    {

        flag= -1; // empty cloud
    }

    emit finished();
    return flag;

}

void CloudControl::readyToAdd()
{
    pcl::PointXYZRGB first=*(rgbCloudPtr->begin ());
    pcl::PointXYZRGB mid=*(rgbCloudPtr->begin ()+rgbCloudPtr->size ()/2);

    if(first.rgb==0&&mid.rgb==0) // 判断第一个点和中间的一个点rgb是否都为0 ，都为零认为没有颜色值默认为黑色则因为窗口背景也为黑时看不到点云，所有设为白色(255,255,255)
    {
        pcl::visualization::PointCloudColorHandlerCustom< pcl::PointXYZRGB> white(rgbCloudPtr,255,255,255);
		cloudViewWidget->getVisuallizer()->removePointCloud();
        cloudViewWidget->getVisuallizer ()->addPointCloud(rgbCloudPtr,white);
		//cloudViewWidget->getVisuallizer()->updatePointCloud(rgbCloudPtr,white);
        cloudViewWidget->getVisuallizer ()->resetCameraViewpoint ();
    }
    else
    {
		//cloudViewWidget->getVisuallizer()->updatePointCloud(rgbCloudPtr);
        addPointCloud(rgbCloudPtr);
    }
	emit cloudupdated();
}

void CloudControl::openCloud(QString cloudFileName)
{

    QDirectStream qout(std::cout);//relocate cout to my log file ,in order to receive information from SFMLibrary
    QObject::connect(&qout,SIGNAL(textReady(QString)),textEdit,SLOT(append(QString))); //connect the QDirectStream textReady to QTextEdit'append.
    
   
	connect(&watcher,SIGNAL(finished()),this,SLOT(readyToAdd()));

	re=QtConcurrent::run(this,&CloudControl::readply,cloudFileName.toStdString());
	watcher.setFuture(re);
    //auto first=*(rgbCloudPtr->begin ());
    //auto mid=*(rgbCloudPtr->begin ()+rgbCloudPtr->size ()/2);

    //if(first.rgb==0&&mid.rgb==0) // 判断第一个点和中间的一个点rgb是否都为0 ，都为零认为没有颜色值默认为黑色则因为窗口背景也为黑时看不到点云，所有设为白色(255,255,255)
    //{
    //    pcl::visualization::PointCloudColorHandlerCustom< pcl::PointXYZRGB> white(rgbCloudPtr,255,255,255);
    //    cloudViewWidget->getVisuallizer ()->addPointCloud(rgbCloudPtr,white);
    //    cloudViewWidget->getVisuallizer ()->resetCameraViewpoint ();
    //}
    //else
    //{
    //    addPointCloud(rgbCloudPtr);
    //}


}



