#include "ConsoleApp.h"
#include "CloudControl.h"
#include <QDir>
#include <QDateTime>
#include <QStringList>
//#include <io.h>
ConsoleApp::ConsoleApp(int arg, char* argv[]):QCoreApplication(arg,argv)
{
    controller.reset(new CloudControl());
    //logbuf=new std::streambuf();

    QString logName=QString("LOG%1_%2.txt").arg(QDate::currentDate().toString("yyyy.MM.dd"),QTime::currentTime().toString("hh.mm"));
	logName.insert(0,QCoreApplication::arguments()[1].append('\\'));
    logFile=new  std::ofstream(logName.toStdString().c_str());
    coutbuf=std::cout.rdbuf(logFile->rdbuf());

    if(arg>2)
        cloudName=QString("cloud_%1.ply").arg(QString(argv[2]));
    else cloudName="cloud.ply";

}


ConsoleApp::~ConsoleApp(void)
{


    delete logFile;

}

void ConsoleApp::compute()
{

    QString filepath= QCoreApplication:: arguments()[1];
    QDir dir(filepath);

    QStringList filters;
    filters << "*.jpg" << "*.png" ;
    dir.setNameFilters(filters);
    QStringList filelist= dir.entryList();

    QStringList::Iterator it = filelist.begin();
     while(it != filelist.end()) {
         (*it).insert(0,filepath.append('\\'));
         ++it;
     }
     cloudName.insert(0,filepath.append('\\'));
    controller->setFiles(filelist);
    controller->consoleCompute();
    controller->saveCameraDistortionMat();
    controller->saveCloud(cloudName);
    controller->saveMatches();   //save the final keypoints and matches to file;


    logFile->flush(); // close logFile and make std::cout normally
    logFile->close();
    std::cout.rdbuf(coutbuf);


    if(arguments().size()>2)
    {
        unsigned long int numberofMatches=0;//controller->getDistance()->getMatches_matrix()[std::make_pair(0,1)].size();
        std::fstream  file;
        QString fileName=arguments()[1];
        fileName+="\\IteratorMatchesData.txt";

        if(access(fileName.toStdString().data(),0)==-1)
        {
            file.open(fileName.toStdString().data(),std::ios_base::app);
            file<<"Iteratation"<<" "<<"Num_of_Matches"<<std::endl;
            file<<arguments()[2].toInt()<<" "<<numberofMatches<<std::endl;
        }
        else
        {
            file.open(fileName.toStdString().data(),std::ios_base::app);
            file<<arguments()[2].toInt()<<" "<<numberofMatches<<std::endl;
        }
    }


}
