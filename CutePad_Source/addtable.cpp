/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "addtable.h"
#include "ui_addtable.h"


addTable::addTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTable)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(5);
    textEdit = new QTextEdit();
    startUp();
    checkDrag = true;
    this->installEventFilter(this);
}

addTable::~addTable()
{
    delete timer;
    delete ui;
}
void addTable::startUp()
 {

    alignment  = Qt::AlignCenter;
    color = Qt::white;
    border = Qt::black;
     ui->label_9->setStyleSheet(QString("background : %1;border : 1px solid black;").arg(border.name()));
    ui->label_7->setStyleSheet(QString("background : %1;border : 1px solid black;").arg(color.name()));
     setTable(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value(),
              ui->spinBox_4->value(),color,border,alignment);
 }

void addTable::on_spinBox_valueChanged(int rows )
{

    setTable(rows,ui->spinBox_2->value(),ui->spinBox_3->value(),ui->spinBox_4->value(),
             color,border,alignment);
}


void addTable::on_spinBox_2_valueChanged(int col )
{

    setTable(ui->spinBox->value(),col,ui->spinBox_3->value(),ui->spinBox_4->value(),
             color,border,alignment);

}

void addTable::on_spinBox_3_valueChanged(int space)
{
    setTable(ui->spinBox->value(),ui->spinBox_2->value(),space,ui->spinBox_4->value(),
             color,border,alignment);

}

void addTable::on_spinBox_4_valueChanged(int padding)
{
    setTable(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value(),
             padding,color,border,alignment);

}
void  addTable::setTable(int rows,int columns,int spacing,int padding,
                         QColor background,QColor border,Qt::Alignment alignment)
  {
    ui->textEdit->clear();

    format.setCellSpacing(spacing);
    format.setCellPadding(padding);
    format.setBackground(QBrush(background));
    format.setBorderBrush(QBrush(border));
    QTextCursor cursor =  ui->textEdit->textCursor();
    format.setAlignment(alignment);
    cursor.insertTable(rows,columns,format);

  }

void addTable::on_pushButton_clicked()
{
    color = QColorDialog::getColor(Qt::white, this, "Pick a Color",
                                   QColorDialog::DontUseNativeDialog);
    if (color.isValid())
    {

       ui->label_7->setStyleSheet(QString("background : %1;border : 1px solid black;").arg(color.name()));
        setTable(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value(),
                 ui->spinBox_4->value(),color,border,alignment);
    }
}

void addTable::on_pushButton_2_clicked()
{
    border = QColorDialog::getColor(Qt::black, this, "Pick a Color",
                                    QColorDialog::DontUseNativeDialog);
    if (border.isValid())
    {

       ui->label_9->setStyleSheet(QString("background : %1;border : 1px solid black;").arg(border.name()));
        setTable(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value(),
                 ui->spinBox_4->value(),color,border,alignment);
    }
}

void addTable::on_comboBox_currentIndexChanged(int index)
{

    if(index == 0)
    {
         alignment = Qt::AlignLeft;
    }
    else if(index == 1)
    {
        alignment = Qt::AlignCenter;
    }
    else if(index == 2)
    {
         alignment = Qt::AlignRight;
    }
     setTable(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value(),
              ui->spinBox_4->value(),color,border,alignment);
}



void addTable::on_cancelButton_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(5);
}

void addTable::on_insertButton_clicked()
{
  QTextCursor cursor= textEdit->textCursor();
  cursor.insertTable(ui->spinBox->value(),ui->spinBox_2->value(),format);
  disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
  connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
  timer->start(5);


}
 void addTable::getTextEdit(QTextEdit *text)
 {

       textEdit = text;
 }
void addTable::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}
void addTable::closingWindow()
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

void addTable::on_toolButton_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
    timer->start(5);
}
void addTable::getLocation(int x,int y)
{
     this->move(QPoint(x,y));
}
bool addTable::eventFilter( QObject *dist, QEvent *event )
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
