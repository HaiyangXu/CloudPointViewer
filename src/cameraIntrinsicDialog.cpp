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

#include "cameraIntrinsicDialog.h"
#include "ui_cameraIntrinsicDialog.h"

cameraIntrinsicDialog::cameraIntrinsicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cameraIntrinsicDialog)
{
    ui->setupUi(this);
}

cameraIntrinsicDialog::~cameraIntrinsicDialog()
{
    delete ui;
}

QStringList cameraIntrinsicDialog::getCameraMat()
{
    QStringList matList;
    matList.append(ui->cameraMat_0->text());
    matList.append(ui->cameraMat_1->text());
    matList.append(ui->cameraMat_2->text());
    matList.append(ui->cameraMat_3->text());
    matList.append(ui->cameraMat_4->text());
    matList.append(ui->cameraMat_5->text());
    matList.append(ui->cameraMat_6->text());
    matList.append(ui->cameraMat_7->text());
    matList.append(ui->cameraMat_8->text());

    matList.append(ui->cameraMat_9->text());
    matList.append(ui->cameraMat_10->text());
    matList.append(ui->cameraMat_11->text());
    matList.append(ui->cameraMat_12->text());

    return matList;
}

void cameraIntrinsicDialog::on_buttonBox_accepted()
{
     accept();
}

void cameraIntrinsicDialog::on_buttonBox_rejected()
{
     reject();
}
