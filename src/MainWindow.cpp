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

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "aboutDialog.h"
#include <QString>
#include <qdatetime.h>
#include <QFileDialog>
#include <pcl/point_cloud.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include "cameraIntrinsicDialog.h"
#include "CloudView.h"
#include <QLabel>
#include <QProgressDialog>
#include <QtUiTools/QUiLoader>
#include <QLineEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionNextImagePair->setDisabled (true);
    ui->actionPreImagePair->setDisabled (true);
	controller=new CloudControl(ui->textEdit);
//    setCentralWidget(new PCLQWidget());  
//    view=dynamic_cast<PCLQWidget *> (centralWidget());
//    view->setRenderMode(POINT_CLOUD_MODE);
//    view->addPointCloud(controller->cloudPtr,"Default");
//    //view->setBackgroundRole();

    setCentralWidget (controller->getCloudViewWidget ());
    //ui->logDockWidget->setGeometry(this->frameGeometry().x()+this->frameGeometry().width()+10,this->geometry().y(),200,this->height());

}

MainWindow::~MainWindow()
{
//    save the logs into files
    QFile file( QString("LOG%1_%2.txt").arg(QDate::currentDate().toString("yyyy.MM.dd"),QTime::currentTime().toString("hh.mm")));
	//QFile file("log.txt");
   if (file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QTextStream out(&file);
         out << ui->textEdit->document()->toPlainText();
     }
    file.close();
    delete ui;
}

void MainWindow::on_actionOpen_Cloud_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Point Cloud"), "./" , tr("Point Cloud Files (*.ply)"));
	QString txt ="Opening Cloud :"+fileName;//QString("Opening:").append (cloudFileName.c_str ());
	if(!fileName.isEmpty())
	{
		QProgressDialog *p=new QProgressDialog( txt,QString(),0, 0, this);
		p->setWindowModality(Qt::WindowModal);
		p->setVisible(true);
		connect(controller, SIGNAL(finished()), p, SLOT(accept()));
		//connect(controller,SIGNAL(finished()),this,SLOT(hide()));
		//connect(this,SIGNAL(hided()),this,SLOT(show()));

		controller->openCloud (fileName);
	}
//    view->addPointCloud(controller->cloudPtr,"sample cloud");
//    view->getVisuallizer()->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
//    view->getVisuallizer()->addCoordinateSystem (1.0);
//    view->getVisuallizer()->initCameraParameters ();
//    centralWidget ()->update ();
}

void MainWindow::on_actionNew_Project_triggered()
{

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),QString(),tr("Images (*.png *.xpm *.jpg)"));
    controller->setFiles(fileNames);
}

void MainWindow::on_actionCompute_Cloud_triggered()
{

//    QObject::connect(controller,
//                     SIGNAL(cloudReady(pcl::PointCloud<pcl::PointXYZ>::Ptr)),
//                     controller,
//                     SLOT(addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr))
//                     );
    // asign ui textEdit to controller to receive this process
    //controller->startThreadLog(ui->textEdit);
	controller->start();

}

void MainWindow::on_actionSave_Cloud_triggered()
{

	QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Point Cloud (*.ply)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
	QString fileName;
    if(dialog.exec())
    {
        QStringList fileList= dialog.selectedFiles();
        fileName=fileList.last();
        QFileInfo info(fileName);
        if(info.suffix()!="ply")
        {
			fileName.append(".ply");
        }
    }

	QString txt ="Saving Cloud :"+fileName;//QString("Opening:").append (cloudFileName.c_str ());
	QProgressDialog *p=new QProgressDialog( txt,QString(),0, 0, this);
	p->setWindowModality(Qt::WindowModal);
	p->setVisible(true);
	connect(controller, SIGNAL(finished()), p, SLOT(reset()));

	QtConcurrent::run(controller,&CloudControl::saveCloud,fileName);
    

//    pcl::PLYWriter writer;
//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::AnyFile);
//    dialog.setNameFilter(tr("Point Cloud (*.ply)"));
//    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    if(dialog.exec())
//    {
//        QStringList fileList= dialog.selectedFiles();
//        QString fileName=fileList.last();
//        QFileInfo info(fileName);
//        if(info.suffix()=="ply")
//        writer.write(fileName.toStdString(),(*controller->cloudPtr));
//    }

}

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog a(this);
    if(a.exec());
}

void MainWindow::on_actionCamera_Matrix_triggered()
{
    cameraIntrinsicDialog cameraDialog(this);
    if(cameraDialog.exec())
    {
        QStringList matList=cameraDialog.getCameraMat();
        controller->saveCameraDistortionMat(matList);
    }

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCMVS_triggered()
{
    controller->cmvs();
}

void MainWindow::on_actionLog_Window_toggled(bool arg1)
{
    if(arg1)ui->logDockWidget->setGeometry(this->frameGeometry().x()+this->frameGeometry().width()+10,this->geometry().y(),200,this->height());
    ui->logDockWidget->setVisible(arg1);
}

void MainWindow::on_actionSetting_triggered()
{

}

void MainWindow::on_actionMatches_triggered(bool checked)
{
    if(checked)
    {	

        setCentralWidget (controller->getImageViewWidget ());
        ui->actionNextImagePair->setEnabled (true);
        ui->actionPreImagePair->setEnabled (true);
    }
    else
	{
        ui->actionNextImagePair->setDisabled (true);
        ui->actionPreImagePair->setDisabled (true);
        setCentralWidget (controller->getCloudViewWidget ());
	}
}

void MainWindow::on_actionNextImagePair_triggered()
{
    controller->showMatches (1);
}

void MainWindow::on_actionPreImagePair_triggered()
{
    controller->showMatches (-1);

}

void MainWindow::on_actionRadiusOutlier_triggered()
{
    //load RadiusOutlier Ui
    QUiLoader loader;
    QFile file(":/forms/RadiusOutlier.ui");
    file.open(QFile::ReadOnly);

    QDialog *radiusOutlierForm = dynamic_cast<QDialog *>(loader.load(&file, this));
    file.close();



    if(radiusOutlierForm->exec()==QDialog::Accepted)
    {
        while(radiusOutlierForm->isVisible());//untill it closed
        QLineEdit *r=radiusOutlierForm->findChild<QLineEdit *>("radius");
        QLineEdit *n=radiusOutlierForm->findChild<QLineEdit *>("neighbor");


        QString txt ="Applying RadiusOut filter to the cloud ...";
        QProgressDialog *p=new QProgressDialog( txt,QString(),0, 0, this);
        p->setWindowModality(Qt::WindowModal);
        p->setVisible(true);
        connect(controller, SIGNAL(finished()), p, SLOT(reset()));

        QtConcurrent::run(controller,&CloudControl::filter,r->text().toDouble(),n->text().toInt(),0);
        //int re=controller->RadiusOutlier(r->text().toDouble(),n->text().toInt());
    }



}

void MainWindow::on_actionStatisticalRemoval_triggered()
{
    //load RadiusOutlier Ui
    QUiLoader loader;
    QFile file(":/forms/StatisticalRemoval.ui");
    file.open(QFile::ReadOnly);

    QDialog *statisticalRemovalForm = dynamic_cast<QDialog *>(loader.load(&file, this));
    file.close();

    if(statisticalRemovalForm->exec()==QDialog::Accepted)
    {
        while(statisticalRemovalForm->isVisible());//untill it closed
        QLineEdit *std=statisticalRemovalForm->findChild<QLineEdit *>("stddev");
        QLineEdit *n=statisticalRemovalForm->findChild<QLineEdit *>("neighbor");


        QString txt ="Applying Statistical filter to the cloud ...";
        QProgressDialog *p=new QProgressDialog( txt,QString(),0, 0, this);
        p->setWindowModality(Qt::WindowModal);
        p->setVisible(true);
        connect(controller, SIGNAL(finished()), p, SLOT(reset()));

        QtConcurrent::run(controller,&CloudControl::filter,std->text().toDouble(),n->text().toInt(),1);
        //int re=controller->RadiusOutlier(r->text().toDouble(),n->text().toInt());
    }
}
