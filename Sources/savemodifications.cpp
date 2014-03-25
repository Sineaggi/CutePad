/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "savemodifications.h"
#include "ui_savemodifications.h"

SaveModifications::SaveModifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveModifications)
{
    ui->setupUi(this);
     this->setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(10);
    textEdit = new QTextEdit;
    tabWidget = new QTabWidget;
    lineEdit = new QLineEdit;
    fileName = new QString;
    label = new QLabel;
    reset = new bool;
    checkDrag = true;
    this->installEventFilter(this);
}
void SaveModifications::getLocation(int x,int y)
{
    this->move(QPoint(x,y));
}

SaveModifications::~SaveModifications()
{

    delete timer;
    delete ui;

}
void SaveModifications::getWidgets(QTextEdit *editor
                                   ,QTabWidget *tab
                                   ,QString &file
                                   ,QLineEdit *lEdit
                                   ,bool fExists
                                   ,QLabel *mlabel
                                   ,bool &RESET )
 {
    lineEdit = lEdit;
    fileName = &file;
    tabWidget = tab;
    textEdit = editor;
    fileExists = fExists;
    label = mlabel;
    reset = &RESET;

 }

void SaveModifications::on_pushButton_clicked()
{
    //save

    if (fileName->isEmpty())
    {
        if(fileSaveAs())
        {
            if(save())
            {
                doWork(false);
            }
        }
        else
        {
            if(!fileName->isEmpty())
            {
                doWork(true);
            }
        }
    }
    else
    {
        if(fileExists)
        {
            if(save())
            {
                doWork(false);
            }
        }
        else
        {
            doWork(true);
        }
    }
}

void SaveModifications::on_pushButton_3_clicked()
{
    //dont save

    doWork(false);

}

void SaveModifications::on_pushButton_2_clicked()
{
    //cancel
   *reset = false;
   disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
   connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
   timer->start(10);
}
bool  SaveModifications::save()
{
    QTextDocumentWriter writer(*fileName);
    bool success = writer.write(textEdit->document());
    if (success)
        textEdit->document()->setModified(false);
    return success;
}
bool SaveModifications::fileSaveAs()
{
    QString *currentFilter  = new QString;
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
    // FIXME: Add error check for empty array
    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0]+
    "/"+textEdit->documentTitle(),
    tr(
    "Text Documents(*.txt);;"
    "HTML-Files(*.htm *.html);;"
    "All Files (*)")
    ,currentFilter);

    if (fn.isEmpty())
        return false;
    if(*currentFilter == "Text Documents(*.txt)")
    {
        if (!(fn.endsWith(".txt", Qt::CaseInsensitive)))
        fn += ".txt";
        *fileName = fn;
         fileExists = false;
        return false;
    }
    else if(*currentFilter =="HTML-Files(*.htm *.html)")
    {
        if (!(fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)))
        fn += ".html";
        *fileName = fn;
         fileExists = true;
         return true;
    }
    else if(*currentFilter =="All Files (*)")
    {
        *fileName = fn;
         fileExists = false;
        return false;
    }

    return true;

}
void SaveModifications::Write(QString *fileName)
 {
     QFile file(*fileName);
     if(!file.open(QFile::WriteOnly | QFile::Text))
     {
         QMessageBox::critical(this,"Error :","Error : File can not be open to write"
                               "\nPlease contact system administrator ...");
         return;

     }
    QTextStream out(&file);
    out << textEdit->document()->toPlainText();
    out.flush();
    file.close();
 }
void SaveModifications::doWork(bool stat)
  {


      *reset = true;
      if(stat)
      {
             Write(fileName);
      }
      textEdit->clear();
      *fileName  = "";
      textEdit->setDocumentTitle("Untitled");
      textEdit->document()->setModified(false);
      lineEdit->setText("Untitled");
      lineEdit->setReadOnly(false);
      label->setText("Not Saved");
      tabWidget->setCurrentIndex(0);

      disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
      connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
      timer->start(10);
  }
void SaveModifications::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.05;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }

}

void SaveModifications::closingWindow()
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
bool SaveModifications::eventFilter( QObject *dist, QEvent *event )
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
