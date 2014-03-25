/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */



#include "about.h"
#include "ui_about.h"


About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(this->width(),this->height());
    QSettings set(QSettings::IniFormat, QSettings::UserScope,
                           "Serandibosft", "CutePad");
    ui->versionLabel->setText(set.value("version",0.1).toString());
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(20);
    checkDrag = true;

}

About::~About()
{
    delete timer;
    delete ui;
}
void About::mouseReleaseEvent(QMouseEvent *)
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(20);
}

void About::getLocation(int x,int y)
{
    this->move(QPoint(x,y));
}
void About::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}
void About::closingWindow()
{
    double r = this->windowOpacity();
    r = r-0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 0)
    {
        timer->stop();
        close();
    }

}

void About::on_pushButton_clicked()
{
    this->setStyleSheet("QDialog{"
            "background: white;"
            "}");
    this->setWindowOpacity(0);
    qApp->aboutQt();
     this->setStyleSheet("QDialog{"
         " background : white; "
         " Image : url(:/Images/Images/About.png);"
          "border : 4px solid gray;"
         "}");
    this->setWindowOpacity(1);
}

void About::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl("mailto:serandibsoft@gmail.com", QUrl::TolerantMode));
}

void About::on_pushButton_3_clicked()
{
     QDesktopServices::openUrl(QUrl("http://serandibsoft.weebly.com", QUrl::TolerantMode));
}

void About::on_toolButton_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(20);
}
