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
#include "ConsoleApp.h"
#include <QApplication>
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    if (argc>1)
    {


            ConsoleApp console(argc,argv);
            console.compute();

            return 0;
    }

    else
    {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
    }
}
