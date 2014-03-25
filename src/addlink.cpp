/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */


#include "addlink.h"
#include "ui_addlink.h"

addLink::addLink(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::addLink)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(5);
    checkDrag = true;
    this->installEventFilter(this);
    ui->lineEdit->setFocus(Qt::MouseFocusReason);
    ui->label_23->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);

}

addLink::~addLink()
{
    delete timer;
    delete ui;
}


void addLink::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}
void addLink::closingWindow()
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



void addLink::on_toolButton_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(10);

}
void addLink::getTextEdit(QTextEdit *textEdit)
{
edit = new QTextEdit();
    edit = textEdit;

    QTextCursor cursor = edit->textCursor();
    if(cursor.hasSelection())
    {
        if(!cursor.selectedText().isEmpty())

        {
            ui->lineEdit->setText(cursor.selectedText());
        }
    }

}

void addLink::on_pushButton_clicked()
{

    QTextCursor cursor = edit->textCursor();

    if(ui->lineEdit->text() != "")
    {
        if(ui->radioButton->isChecked() && ui->lineEdit_2->text().isEmpty())
        {
            return;
        }
        if(ui->radioButton_2->isChecked() && ui->lineEdit_3->text().isEmpty())
        {
            return;
        }
        QString text = ui->lineEdit->text();
        QString address  = ui->lineEdit_2->text();
        if(ui->radioButton_2->isChecked())
        {
            address = "mailto:" + ui->lineEdit_3->text();
        }

       QString html = QString("<div><a href = \"%1\" >%2</a>").arg(address).arg(text);

      //  cursor.insertHtml(html);

        cursor.insertHtml(html);
        edit->setTextCursor(cursor);

        disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
        connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
        timer->start(10);
    }
   else
    {
      return;
    }
}

void addLink::on_pushButton_2_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(10);
}
void addLink::getLocation(int x,int y)
{
    this->move(QPoint(x,y));
}
bool addLink::eventFilter( QObject *dist, QEvent *event )
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

void addLink::on_radioButton_toggled(bool checked)
{
    if(checked)
    {
        ui->label_22->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
    }
    else
    {
        ui->label_22->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
    }
}


void addLink::on_radioButton_2_toggled(bool checked)
{
    if(checked)
    {
        ui->label_23->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
    }
    else
    {
        ui->label_23->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
    }
}
