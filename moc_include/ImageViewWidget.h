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

#ifndef IMAGEVIEWWIDGET_H
#define IMAGEVIEWWIDGET_H
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
class ImageViewWidget:public QScrollArea
{
private:
    QLabel imagelabel;
    bool leftMousePressState;
    QPoint mousePos;
    double scaleFactor;
    void wheelEvent (QWheelEvent *wheelEvent);
    void mousePressEvent (QMouseEvent *mousePress);
    void mouseReleaseEvent (QMouseEvent *mouseRelease);
    void mouseMoveEvent (QMouseEvent *mouseMove);
    void scaleImage(double factor);
public:
    ImageViewWidget(QWidget *parent = 0);
    void setImage(QImage &image);
};

#endif // IMAGEVIEWWIDGET_H
