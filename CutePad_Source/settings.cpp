/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "settings.h"
#include "ui_settings.h"
#include <QtGui>
#include <QtCore>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(5);
    checkDrag = true;
    this->installEventFilter(this);
    QCoreApplication::setOrganizationName("Serandibosft");
    QCoreApplication::setOrganizationDomain("serandibsoft.com");
    QCoreApplication::setApplicationName("CutePad");
    set = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                           "Serandibosft", "CutePad");
    setProperties();
    isCancel = new bool;
}

Settings::~Settings()
{
    delete timer;
    delete ui;
}
 void Settings::getCancel(bool &cancel)
 {
     isCancel = &cancel;

 }

void Settings::setProperties()
{

    ui->fontComboBox->setCurrentFont(set->value("defaultFont","Lucida Grande")
                                     .value<QFont>());
    ui->horizontalSlider->setValue(set->value("fontSize",10).toInt());
    ui->checkBox_3->setChecked(set->value("checkUpdates",true).toBool());
    QString color = set->value("themeColor","#4f4f4f").toString();
    if(color == "#e64c4c")
        ui->pushButton_18->setChecked(true);
    if(color == "#7842f3")
        ui->pushButton_19->setChecked(true);
    if(color == "#3581ff")
        ui->pushButton_20->setChecked(true);
    if(color == "#27db6b")
        ui->pushButton_21->setChecked(true);
    if(color == "#a8da22")
        ui->pushButton_22->setChecked(true);
    if(color == "#d9c857")
        ui->pushButton_23->setChecked(true);
    if(color == "#f48726")
        ui->pushButton_24->setChecked(true);
    if(color == "#272727")
        ui->pushButton_25->setChecked(true);
    if(color == "#4f4f4f")
        ui->pushButton_27->setChecked(true);
    if(color == "#917054")
        ui->pushButton_26->setChecked(true);
    ui->checkBox_4->setChecked(set->value("savePosition",false).toBool());
    ui->checkBox->setChecked(set->value("randomizeColors",true).toBool());
    ui->checkBox_5->setChecked(set->value("keepFormat",false).toBool());
}

void Settings::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}
void Settings::closingWindow()
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
void Settings::getLocation(int x,int y)
{
     this->move(QPoint(x,y));
}
bool Settings::eventFilter( QObject *dist, QEvent *event )
{
  if( dist == this && event->type() == QEvent::MouseButtonPress)
  {
      if(checkDrag==true && this->isMaximized() == false)
      {
          drag = true;
          mousex =  QCursor::pos().x() - this->x();
          mousey =  QCursor::pos().y() - this->y();

      }

      return true;
  }
  if( dist == this && event->type() == QEvent::MouseMove)
  {
      if(drag )
      {

          this->setGeometry(QRect(QCursor::pos().x()-mousex , QCursor::pos().y()-mousey ,
                                  this->width(),this->height() ));

      }
      return true;
  }
  if( dist == this && event->type() == QEvent::MouseButtonRelease)
  {
      drag = false;
      return true;
  }

  return false;
}

void Settings::on_toolButton_clicked()
{
    *isCancel = true;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(5);
}

void Settings::on_pushButton_2_clicked()
{
    *isCancel = true;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(5);
}

void Settings::applyChanges()
 {

    if(ui->checkBox->isChecked())
    {
       set->setValue("randomizeColors",true);
    }
    else
    {
        set->setValue("randomizeColors",false);
    }
    if(ui->checkBox_4->isChecked())
    {
         set->setValue("savePosition",true);
    }
    else
    {
         set->setValue("savePosition",false);
    }
    set->setValue("defaultFont",ui->fontComboBox->currentText());
    set->setValue("fontSize",ui->horizontalSlider->value());
    if(ui->checkBox_3->isChecked())
    {
         set->setValue("checkUpdates",true);
    }
    else
    {
         set->setValue("checkUpdates",false);
    }
    if(ui->checkBox_5->isChecked())
    {
        set->setValue("keepFormat",true);
    }
    else
    {
        set->setValue("keepFormat",false);
    }
set->sync();
 }

void Settings::on_pushButton_3_clicked()
{
    applyChanges();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(5);
}

void Settings::on_pushButton_18_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#e64c4c");
    }
}


void Settings::on_pushButton_19_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#7842f3");
    }
}

void Settings::on_pushButton_20_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#3581ff");
    }
}

void Settings::on_pushButton_21_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#27db6b");
    }
}

void Settings::on_pushButton_22_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#a8da22");
    }
}

void Settings::on_pushButton_23_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#d9c857");
    }
}

void Settings::on_pushButton_24_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#f48726");
    }
}

void Settings::on_pushButton_25_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#272727");
    }
}

void Settings::on_pushButton_27_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#4f4f4f");
    }
}

void Settings::on_pushButton_26_clicked(bool checked)
{
    if(checked)
    {
        set->setValue("themeColor","#917054");
    }
}

void Settings::on_pushButton_4_clicked()
{
    //Reset all settings

    set->setValue("isFirstTime",false);
    set->setValue("defaultFont","Lucida Grande");
    set->setValue("fontSize",10);
    set->setValue("checkUpdates",true);
    set->setValue("themeColor","#272727"); //default color
    set->setValue("savePosition",false);
    set->setValue("randomizeColors",true);
    set->setValue("isMaximise",false);
    set->setValue("geometry",this->geometry());
    set->setValue("version",0.1);
    set->setValue("keepFormat",false);

    setProperties();
}
