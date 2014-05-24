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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "CloudControl.h"
#include "CloudView.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpen_Cloud_triggered();

    void on_actionNew_Project_triggered();

    void on_actionCompute_Cloud_triggered();

    void on_actionSave_Cloud_triggered();

    void on_actionAbout_triggered();

    void on_actionCamera_Matrix_triggered();

    void on_actionExit_triggered();

    void on_actionCMVS_triggered();

    void on_actionLog_Window_toggled(bool arg1);

    void on_actionSetting_triggered();

    void on_actionMatches_triggered(bool checked);

    void on_actionNextImagePair_triggered();

    void on_actionPreImagePair_triggered();

    void on_actionRadiusOutlier_triggered();

    void on_actionStatisticalRemoval_triggered();

private:
    Ui::MainWindow *ui;
    CloudControl * controller;
};

#endif // MAINWINDOW_H
