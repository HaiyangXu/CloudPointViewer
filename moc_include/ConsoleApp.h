#pragma once
#include <QCoreApplication>
#include <CloudControl.h>
#include <QScopedPointer>
class ConsoleApp:public QCoreApplication
{
public:
	ConsoleApp(int arg, char* argv[]);
	~ConsoleApp(void);
    void compute();

private:
    QScopedPointer< CloudControl> controller;
    QTextStream logout;
    std::streambuf *coutbuf;
    std::ofstream *logFile;
    QString cloudName;
};









struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer )
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

private:
    std::streambuf * old;
};
