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

#ifndef CAMERAINTRINSICDIALOG_H
#define CAMERAINTRINSICDIALOG_H

#include <QDialog>

namespace Ui {
class cameraIntrinsicDialog;
}

class cameraIntrinsicDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit cameraIntrinsicDialog(QWidget *parent = 0);
    ~cameraIntrinsicDialog();
    QStringList getCameraMat();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::cameraIntrinsicDialog *ui;
};

#endif // CAMERAINTRINSICDIALOG_H
