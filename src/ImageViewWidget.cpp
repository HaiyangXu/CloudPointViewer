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
#include <QScrollBar>
#include "ImageViewWidget.h"
#include <math.h>
ImageViewWidget::ImageViewWidget(QWidget *parent):QScrollArea(parent), scaleFactor(1.0)
{
    //setCursor (Qt::OpenHandCursor);
    setWidget (&imagelabel);
    setCursor (Qt::OpenHandCursor);
    imagelabel.setScaledContents (true);
}
void ImageViewWidget::wheelEvent (QWheelEvent *wheelEvent)
{
    int numDegrees = wheelEvent->delta() / 8;
    int numSteps = numDegrees / 15;

    if(numSteps>0&&scaleFactor<5)
    {
        scaleImage (pow(1.25,numSteps));
    }
    else 
    {
        scaleImage (pow(0.8,-numSteps));
    }

    //scrollVertically(numSteps);

    wheelEvent->accept();
}

void ImageViewWidget::mousePressEvent (QMouseEvent *mousePress)
{
    if(mousePress->buttons()&Qt::LeftButton)
    {
        leftMousePressState=true;
        mousePos=mousePress->pos ();
        setCursor (Qt::ClosedHandCursor);
        mousePress->accept ();
    }
}
void ImageViewWidget::mouseReleaseEvent (QMouseEvent *mouseRelease)
{
    if(mouseRelease->button ()==Qt::LeftButton&&leftMousePressState)
    {
        leftMousePressState=false;
        setCursor (Qt::OpenHandCursor);
    }
}

void ImageViewWidget::mouseMoveEvent (QMouseEvent *mouseMove)
{
    if((mouseMove->buttons() & Qt::LeftButton)&&leftMousePressState)
    {
        QPoint tempPos=mouseMove->pos ();
        horizontalScrollBar ()->setValue (horizontalScrollBar ()->value ()+ (mousePos.x()-tempPos.x ())/10);
        verticalScrollBar ()->setValue (verticalScrollBar ()->value ()+ (mousePos.y ()-tempPos.y ())/10);
        mouseMove->accept ();


    }

}

void ImageViewWidget::setImage (QImage &image)
{
    imagelabel.setPixmap (QPixmap::fromImage (image));
    imagelabel.resize (this->size ());
    //imagelabel.update ();
}

void ImageViewWidget::scaleImage (double factor)
{
    scaleFactor *= factor;
    imagelabel.resize(scaleFactor * imagelabel.pixmap()->size());

    QScrollBar *hScrollBar= this->horizontalScrollBar ();
    QScrollBar *vScrollBar= this->verticalScrollBar ();

    hScrollBar->setValue(int(factor * hScrollBar->value ()
                             +((factor - 1) * hScrollBar->pageStep()/2)));
    vScrollBar->setValue(int(factor * vScrollBar->value ()
                             +((factor - 1) * vScrollBar->pageStep()/2)));
}
