#include "dotask.h"

DoTask::DoTask(QObject *parent) :
    QObject(parent)
{

    dialog = new QDialog;
    timer = new QTimer;
}
void DoTask::start(QDialog *d)
{
    dialog = d;
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    dialog->exec();
    timer->start(100);
}

void DoTask::startingWindow()
{
    double r = dialog->windowOpacity();
    r = r+0.05;
    dialog->setWindowOpacity(r);
    if(dialog->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}
void DoTask::closingWindow()
{
    double r = dialog->windowOpacity();
    r = r-0.05;
    dialog->setWindowOpacity(r);
    if(dialog->windowOpacity() == 0)
    {
        timer->stop();
        dialog->close();
    }

}
