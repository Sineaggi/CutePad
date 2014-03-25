/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centerForm();
    setFrameless();
    ui->statusBar->setFixedHeight(9);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
    timer->start(5);
    setMargin(15);
    checkDrag = true;
    matchCase = false;
    wholeWordsOnly = false;
    fileName = "";
    updateToolTip("Not Saved");

    set = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                           "Serandibosft", "CutePad");

    setupActions();
    dark = new Dark;

    opacity = new  QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.1);
    setUserName();
    ui->frame_5->installEventFilter(this);
    setTextEditDefault();
    setSettings();
    ui->textEdit->document()->setModified(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->textEdit->setDocumentTitle(ui->lineEdit->text());

}
void MainWindow::setSettings()
 {
     QCoreApplication::setOrganizationName("Serandibosft");
     QCoreApplication::setOrganizationDomain("serandibsoft.com");
     QCoreApplication::setApplicationName("CutePad");


     if(!set->contains("isFirstTime"))
     {
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

     }
       set->setValue("version",0.1);
       ui->tabWidget->setCurrentIndex(1);
       ui->tabWidget_2->setCurrentIndex(0);

       ui->fontComboBox->setCurrentFont(set->value("defaultFont","Lucida Grande").value<QFont>());
       ui->horizontalSlider->setValue(set->value("fontSize",10).toInt());
       ui->label_8->setText(QString::number(set->value("fontSize",10).toInt()));
       ui->tabWidget->setCurrentIndex(0);
       ui->tabWidget_2->setCurrentIndex(0);
       setFont(set->value("defaultFont","Lucida Grande").value<QFont>());
       textSize(set->value("fontSize",10).toInt());
       ui->textEdit->setFont(set->value("defaultFont","Lucida Grande").value<QFont>());
       ui->textEdit->setFontPointSize(set->value("fontSize",10).toInt());

       if(set->value("checkUpdates",true).toBool() == true)
       {
           check();
       }
       if(set->value("randomizeColors",true).toBool() == true)
       {

           QStringList colors;
           colors << "#e64c4c" << "#7842f3"
                   <<"#3581ff" <<"#27db6b"
                   <<"#a8da22" <<"#d9c857"
                   <<"#f48726" <<"#272727"
                   <<"#4f4f4f" <<"#917054" ;
           //creates seeds for randomizing
           QTime time = QTime::currentTime();
           qsrand((uint)time.msec());
           int rand =  qrand() % ((9 + 1) - (1)) + (1);
           ui->frame_4->setStyleSheet(QString("background : %1;"
                                             " QLabel{"
                                             "background : none;"
                                             "color : white;"
                                             "}"
                                             )
                                      .arg(colors.at(rand)));
           ui->lineEdit->setStyleSheet(QString("color : white;"
                                       "background : %1;")
                                       .arg(colors.at(rand)));
          set->setValue("themeColor",colors.at(rand));
       }
       else
       {
          ui->frame_4->setStyleSheet(QString("background : %1;"
                                             "QLabel{"
                                             "background : none;"
                                             "color : white;"
                                             "}"
                                             )
                                     .arg(set->value("themeColor","#272727")
                                          .toString()));
          ui->lineEdit->setStyleSheet(QString("color : white;"
                                      "background : %1;")
                                      .arg(set->value("themeColor","#272727")
                                      .toString()));
       }

       if(set->value("savePosition",false).toBool() == true)
       {
           if(set->value("isMaximise",false).toBool() == true)
           {
               ui->toolButton_2->click();
           }
           else
           {
               this->setGeometry(set->value("geometry",this->geometry()).toRect());
           }
       }
      ui->textEdit->setAcceptRichText(set->value("keepFormat",false).toBool());
      set->sync();



 }
void MainWindow::check()
 {
    checkUpdates *updates = new checkUpdates(this);
    updates->getParent(this);
    updates->doCheck();
 }

void  MainWindow::centerForm()
 {
      int x = (QApplication::desktop()->width() - this->width() )/2;
      int y = (QApplication::desktop()->height() - this->height() )/2;
      this->setGeometry(x,y,this->width(),this->height());
 }

void MainWindow::closeEvent(QCloseEvent *e)
 {

    if(set->value("savePosition",false) == true)
    {
        if(this->isMaximized())
        {
            set->setValue("isMaximise",true);
        }
        else
        {
             set->setValue("isMaximise",false);
             set->setValue("geometry",this->geometry());
        }

    }
set->sync();

    if(checkForSave())
   {
        reset = false;
        e->ignore();

//#ifndef SAVEMODIFICATIONS
        dim();
        SaveModifications save;
        save.getWidgets(ui->textEdit,ui->tabWidget,fileName,
                         ui->lineEdit,fileExists,ui->label_3
                         ,reset);
        save.setModal(true);
        int x = this->x()+((this->width()-save.width())/2);
        int y = this->y()+((this->height()-save.height())/2);
        save.getLocation(x,y);
        save.exec();
        dark->close();
//#endif

        if(reset)
        {
            disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
            connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
            timer->start(5);
        }

    }
    else
    {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
        connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
        timer->start(5);
        e->accept();
    }
 }
void MainWindow::setUserName()
{
    QByteArray userName = qgetenv("USERNAME");
    ui->label_19->setStyleSheet("color : gray;");
    ui->label_19->setText(userName.toUpper());
}

void MainWindow::setupActions()
{

    QMenu *printMenu = new QMenu(tr("&Print"), this);
    QAction *a;

    a = new QAction(QIcon(), tr("&Print"), this);
    connect(a, SIGNAL(triggered()), this, SLOT(print()));
    printMenu->addAction(a);

    a = new QAction(QIcon(),tr("&Print Preview"), this);
    connect(a, SIGNAL(triggered()), this, SLOT(printPreview()));
    printMenu->addAction(a);

    ui->printButton->setMenu(printMenu);
}

void MainWindow::printPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
   connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
   preview.setMinimumSize(690,663);
   preview.setWindowTitle("Print preview : " + ui->textEdit->documentTitle());
    preview.exec();
}
void MainWindow::print()
{
    QTextDocument *document = ui->textEdit->document();
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
        return;
    document->print(&printer);
}
void MainWindow::printPreview(QPrinter *printer)
 {
       ui->textEdit->print(printer);
 }

void MainWindow::startingWindow()
{
    double r = this->windowOpacity();
    r = r+0.02;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 1.0)
    {
        timer->stop();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setFrameless(){
    this->setWindowFlags(Qt::FramelessWindowHint);
}
void MainWindow::on_toolButton_clicked()
{
    //animating close


    if(set->value("savePosition",false) == true)
    {
        if(this->isMaximized())
        {
            set->setValue("isMaximise",true);
        }
        else
        {
             set->setValue("isMaximise",false);
             set->setValue("geometry",this->geometry());
        }

    }
  set->sync();
    if(checkForSave())
   {
        reset = false;
        dim();
        SaveModifications save;
        save.getWidgets(ui->textEdit,ui->tabWidget,fileName,
                         ui->lineEdit,fileExists,ui->label_3
                         ,reset);
        save.setModal(true);
        int x = this->x()+((this->width()-save.width())/2);
        int y = this->y()+((this->height()-save.height())/2);
        save.getLocation(x,y);
        save.exec();
        dark->close();
        if(reset)
        {
            disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
            connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
            timer->start(5);
        }

    }
    else
    {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(startingWindow()));
        connect(timer,SIGNAL(timeout()),this,SLOT(closingWindow()));
        timer->start(5);
    }

}
void MainWindow::closingWindow()
{
    double r = this->windowOpacity();
    r = r-0.02;
    this->setWindowOpacity(r);
    if(this->windowOpacity() == 0)
    {
        timer->stop();
        qApp->quit();
        //close();
    }
}
int MainWindow::countWords()
{
    //Count the number of words in the document...
    txt =  ui->textEdit->toPlainText();
    txt.replace("\n"," ");
    txt.replace("\t"," ");
    words = 0;
    for(int i=0 ; i<txt.count();i++)
    {
        if((i+1) != txt.count())
        {
            QChar a = txt.at(i);
            QChar b = txt.at(i+1);
            if (a == ' ' && b != ' ')
            {
                words++;
            }
        }
    }
    return words+1;
}
void MainWindow::pickColor()
{
    color = QColorDialog::getColor(Qt::green, this, "Pick a Color", QColorDialog::DontUseNativeDialog);
    if (color.isValid())
    {
        QString col = QString("background : %1 ;border:0px solid %1;").arg(color.name());
        ui->pushButton_25->setStyleSheet(col);
        setFontColor(color.rgb());
    }
}
void MainWindow::on_pushButton_24_clicked()
{
    pickColor();
}
//set text formattings
void MainWindow::setBold(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}
void MainWindow::setItalic(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(checked);
    mergeFormatOnWordOrSelection(fmt);
}
void MainWindow::setunderLine(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(checked);
    mergeFormatOnWordOrSelection(fmt);
}
void MainWindow::setStrikeOut(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(checked);
    mergeFormatOnWordOrSelection(fmt);
}
void MainWindow::setSuperScript(bool checked)
{
    QTextCharFormat fmt;
    if(checked)
    {
        ui->subScriptButton->setChecked(false);
        fmt.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    }
    else
    {
        fmt.setVerticalAlignment(QTextCharFormat::AlignNormal);
    }
    mergeFormatOnWordOrSelection(fmt);
}
void MainWindow::setSubScript(bool checked)
{
    QTextCharFormat fmt;
    if(checked)
    {    ui->superScriptButton->setChecked(false);
        fmt.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    }
    else
    {
        fmt.setVerticalAlignment(QTextCharFormat::AlignNormal);
    }
    mergeFormatOnWordOrSelection(fmt);
}

//set text formattings on text edit.
void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


//check for realtime text formatting button changes
void MainWindow::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());

}

void MainWindow::fontChanged(const QFont &f)
{
    ui->label_8->setText(QString::number(f.pointSize()));
    ui->horizontalSlider->setValue(f.pointSize());

    ui->fontComboBox->setCurrentFont(f);
    ui->boldButton->setChecked(f.bold());
    ui->italicButton->setChecked(f.italic());
    ui->underlineButton->setChecked(f.underline());
    // ui->subScriptButton->setChecked();
    ui->strikeoutButton->setChecked(f.strikeOut());

}
void MainWindow::on_textEdit_currentCharFormatChanged(QTextCharFormat format)
{
    currentCharFormatChanged(format);
}

//Set button controls for text formatting

void MainWindow::on_italicButton_clicked(bool checked)
{
    setItalic(checked);
}
void MainWindow::on_underlineButton_clicked(bool checked)
{
    setunderLine(checked);
}
void MainWindow::on_strikeoutButton_clicked(bool checked)
{
    setStrikeOut(checked);
}
void MainWindow::on_boldButton_clicked(bool checked)
{
    setBold(checked);

}
void MainWindow::textSize(int p)
{
    qreal pointSize = p;
    if (p > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    int F_Size = ui->horizontalSlider->value();
    F_Size += 5;
    if(F_Size <= 100)
    {
        textSize(F_Size);
    }
    else
    {
        textSize(100);
    }

}
void MainWindow::on_pushButton_11_clicked()
{
    int F_Size = ui->horizontalSlider->value();
    F_Size -= 5;
    if(F_Size >= 1)
    {
        textSize(F_Size);
    }
    else
    {
        textSize(1);
    }

}

void MainWindow::setFontColor(QRgb RGB)
{
    QColor color;
    color.setRgb(RGB);
    if (!color.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(color);
    mergeFormatOnWordOrSelection(fmt);
}

//set color button actions
void MainWindow::on_pushButton_18_clicked()
{
    setFontColor(qRgb(255,0,0));
}

void MainWindow::on_pushButton_19_clicked()
{
    setFontColor(qRgb(255,156,0));
}

void MainWindow::on_pushButton_20_clicked()
{
    setFontColor(qRgb(255,255,0));
}

void MainWindow::on_pushButton_21_clicked()
{
    setFontColor(qRgb(0,176,80));
}

void MainWindow::on_pushButton_26_clicked()
{
    setFontColor(qRgb(0,77,187));
}

void MainWindow::on_pushButton_27_clicked()
{
    setFontColor(qRgb(155,0,211));
}

void MainWindow::on_pushButton_23_clicked()
{
    setFontColor(qRgb(0,0,0));
}

void MainWindow::on_pushButton_22_clicked()
{
    setFontColor(qRgb(51,51,51));
}

void MainWindow::on_pushButton_17_clicked()
{
    setFontColor(qRgb(102,102,102));
}

void MainWindow::on_pushButton_16_clicked()
{
    setFontColor(qRgb(165,165,165));
}

void MainWindow::on_pushButton_15_clicked()
{
    setFontColor(qRgb(204,204,204));
}

void MainWindow::on_pushButton_14_clicked()
{
    setFontColor(qRgb(255,255,255));
}

void MainWindow::on_pushButton_25_clicked()
{
    QPalette palette = ui->pushButton_25->palette();
    QColor col = palette.color(QPalette::Background);
    setFontColor(col.rgb());
}

void MainWindow::on_fontComboBox_currentFontChanged(QFont f)
{

}
void MainWindow::setFont(QFont font)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(font.family());
    mergeFormatOnWordOrSelection(fmt);
}


void MainWindow::on_fontComboBox_activated(QString fontFamily)
{
    QFont f ;
    f.setFamily(fontFamily);
    setFont(f);
}

void MainWindow::on_subScriptButton_toggled(bool checked)
{
    setSubScript(checked);
}

void MainWindow::on_superScriptButton_toggled(bool checked)
{
    setSuperScript(checked);
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    int value  = ui->horizontalSlider->value();
    ui->label_8->setText(QString::number(value));
    textSize(value);
}

void MainWindow::on_pushButton_12_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setAlignment(Qt::AlignCenter);


    }

}

void MainWindow::on_pushButton_13_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);


    }

}

void MainWindow::on_pushButton_28_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setAlignment(Qt::AlignJustify);


    }

}

void MainWindow::on_pushButton_9_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    }

}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    alignmentChanged(ui->textEdit->alignment());
}
void MainWindow::alignmentChanged(Qt::Alignment a)
{
    if(a & Qt::AlignLeft)
    {
        ui->pushButton_9->setChecked(true);
    }
    else if (a & Qt::AlignHCenter)
    {
        ui->pushButton_12->setChecked(true);
    }
    else if (a & Qt::AlignRight)
    {
        ui->pushButton_13->setChecked(true);
    }
    else if (a & Qt::AlignJustify)
    {
        ui->pushButton_28->setChecked(true);
    }
}

void MainWindow::on_indentDecrease_button_clicked()
{
    //decrease indent

    QTextCursor cursor = ui->textEdit->textCursor();

    QTextBlockFormat tbf = cursor.blockFormat();
    if (tbf.indent() >= 1)
    {
        tbf.setIndent(tbf.indent()-1);
    }
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.setBlockFormat(tbf);

}


void MainWindow::on_indentIncrease_button_clicked()
{
    //increase indent
    QTextCursor cursor = ui->textEdit->textCursor();

    QTextBlockFormat tbf = cursor.blockFormat();
    if (tbf.indent() <= 10)
    {
        tbf.setIndent(tbf.indent()+1);
    }
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.setBlockFormat(tbf);
}



void MainWindow::on_decreaseSpacing_button_clicked()
{
    //set linespace decreasing


    QTextBlockFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    format = cursor.blockFormat();
    if(format.lineHeight()>= 0)
    {
        format.setLineHeight(format.lineHeight()-2,QTextBlockFormat::LineDistanceHeight);
        ui->label_28->setText(QString::number(format.lineHeight()));
    }
    else
    {
        format.setLineHeight(-2,QTextBlockFormat::LineDistanceHeight);
        ui->label_28->setText(QString::number(format.lineHeight()));


    }
    cursor.setBlockFormat(format);

}

void MainWindow::on_increaseSpacing_button_clicked()
{
    //set linespace increasing

    QTextBlockFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    format = cursor.blockFormat();

    if(format.lineHeight()<=40)
    {
        format.setLineHeight(format.lineHeight()+2,QTextBlockFormat::LineDistanceHeight);
        ui->label_28->setText(QString::number(format.lineHeight()));
    }

    cursor.setBlockFormat(format);
}



void MainWindow::on_decreaseSpacing_button_2_toggled(bool checked)
{
    if(checked)
    {

        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }
}

void MainWindow::on_decreaseSpacing_button_3_toggled(bool checked)
{
    if(checked)
    {
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
}
void MainWindow::bulletsNumbering(int index)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (index != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (index) {
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style = QTextListFormat::ListUpperRoman;
            break;
        case 9:
            style = QTextListFormat::ListStyleUndefined;
            break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
            if(index == 9)
            {
                listFmt.setIndent(0);
                blockFmt.setIndent(0);
                cursor.setBlockFormat(blockFmt);
            }
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void MainWindow::on_indentDecrease_button_2_clicked()
{
    bulletsNumbering(2);
}

void MainWindow::on_indentDecrease_button_3_clicked()
{
    bulletsNumbering(1);
}

void MainWindow::on_indentDecrease_button_4_clicked()
{
    bulletsNumbering(3);
}

void MainWindow::on_indentDecrease_button_5_clicked()
{
    bulletsNumbering(4);
}

void MainWindow::on_indentDecrease_button_6_clicked()
{
    bulletsNumbering(5);
}

void MainWindow::on_indentDecrease_button_7_clicked()
{
    bulletsNumbering(6);
}

void MainWindow::on_indentDecrease_button_8_clicked()
{
    bulletsNumbering(7);
}

void MainWindow::on_indentDecrease_button_9_clicked()
{
    bulletsNumbering(8);

}

void MainWindow::on_indentDecrease_button_10_clicked()
{
    bulletsNumbering(9);
}

void MainWindow::setMargin(int margin)
{
    QTextDocument *document  = ui->textEdit->document();
     document->setDocumentMargin(margin);
     ui->textEdit->setDocument(document);
}

void MainWindow::on_toolButton_2_clicked()
{
setWindowState();
}
void MainWindow::setWindowState()
 {

    if (this->isMaximized())
    {
        this->showNormal();
        ui->toolButton_2->setStyleSheet("QToolButton{ "
            "Image : url(:/Images/Images/maximize.png);"
            "background : solid white;"
            "border : 0px  solid white;"
           " color : white;"
           " }"
            "QToolButton:hover , QToolButton:selected{"
           " Image : url(:/Images/Images/maximize_hover.png);"
           " border : 0px  solid  rgb(27,161,226);"
           " color : white;"
           " }");
     ui->toolButton_2->setToolTip("Maximize");

    }
    else
    {
        this->showMaximized();
        ui->toolButton_2->setStyleSheet("QToolButton{ "
            "Image : url(:/Images/Images/normal.png);"
            "background : solid white;"
            "border : 0px  solid white;"
           " color : white;"
           " }"
            "QToolButton:hover , QToolButton:selected{"
           " Image : url(:/Images/Images/normal_hover.png);"
           " border : 0px  solid  rgb(27,161,226);"
           " color : white;"
           " }");
          ui->toolButton_2->setToolTip("Restore Down");
    }
    //this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
 }

void MainWindow::on_setImage_button_clicked()
{
        QString  imagePath = QFileDialog::getOpenFileName(this,
        tr("Open Image"),QDesktopServices::storageLocation
        (QDesktopServices::PicturesLocation),
        tr("Image Files (*.png *.jpg *.bmp)"));
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextCharFormat charFormat = cursor.charFormat();
        QTextImageFormat imageFormat;
        imageFormat.setName(imagePath);
        QPixmap pix;
        pix.load(imagePath);
        QStringList zoomLevel;
        zoomLevel <<"25%"
                <<"50%"
                <<"75%"
                << "100%"
                <<"125%"
                <<"150%"
                <<"175%"
                <<"200%";


        bool ok;
        QString item;
        if(!imagePath.isEmpty())
        {
        item = QInputDialog::getItem(this, tr("Image size"),
                                                 tr("Zoom Level:"), zoomLevel, 3, false, &ok);


        if (ok && !item.isEmpty())
        {
            for(int i=0;i<zoomLevel.count();i++)
            {
                if(item == zoomLevel.at(0))
                {
                    imageFormat.setWidth(pix.width()/4);
                    imageFormat.setHeight( pix.height()/4);
                }
                else if(item == zoomLevel.at(1))
                {
                    imageFormat.setWidth(pix.width()/2);
                    imageFormat.setHeight( pix.height()/2);
                }
                else if(item == zoomLevel.at(2))
                {
                    imageFormat.setWidth((pix.width()/4)*3);
                    imageFormat.setHeight( (pix.height()/4)*3);
                }
                else if(item == zoomLevel.at(3))
                {
                    imageFormat.setWidth(pix.width());
                    imageFormat.setHeight( pix.height());
                }
                else if(item == zoomLevel.at(4))
                {
                    imageFormat.setWidth(pix.width()+(pix.width()/4) );
                    imageFormat.setHeight( pix.height() + (pix.height()/4));
                }
                else if(item == zoomLevel.at(5))
                {
                    imageFormat.setWidth(pix.width()+pix.width()/2);
                    imageFormat.setHeight( pix.height() + pix.height()/2);
                }
                else if(item == zoomLevel.at(6))
                {
                    imageFormat.setWidth( pix.width() + ((pix.width()/4)*3));
                    imageFormat.setHeight(  pix.height() + ((pix.height()/4)*3));
                }
                else if(item == zoomLevel.at(7))
                {
                    imageFormat.setWidth(pix.width()*2);
                    imageFormat.setHeight( pix.height()*2);
                }
             }
        }

        cursor.insertImage(imageFormat);
        cursor.setCharFormat(charFormat);
        ui->textEdit->setTextCursor(cursor);
    }

}

void MainWindow::on_setImage_button_2_clicked()
{
    dim();
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();

    addLink link;
    int x = this->x()+((this->width()-link.width())/2);
    int y = this->y()+((this->height()-link.height())/2);
    link.getLocation(x,y);
    link.getTextEdit(ui->textEdit);
    link.setModal(true);
    link.exec();
       // ui->textEdit->setHtml("<a href =""http://www.serandibsoft.com"">Serandibsoft</a>");
    dark->close();
    cursor.setCharFormat(format);
    ui->textEdit->setTextCursor(cursor);

}


void MainWindow::on_setImage_button_5_clicked()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    QDate date = QDate::currentDate();

    QString format_1 = date.toString("M/d/yyyy");
    QString format_2 = date.toString("dddd, MMMM dd, yyyy");
    QString format_3 = date.toString("MMMM d, yyyy");
    QString format_4 = date.toString("M/d/yy");
    QString format_5 = date.toString("yyyy-MM-dd");
    QString format_6 = date.toString("d-MMM-yy");
    QString format_7 = date.toString("M.d.yyyy");
    QString format_8 = date.toString("d MMMM yyyy");
    QString format_9 = date.toString("MMMM yy");
    QString format_10 = date.toString("MMM-yy");


    QStringList dateFormats;
    dateFormats << format_1
            <<format_2
            <<format_3
            <<format_4
            <<format_5
            <<format_6
            <<format_7
            <<format_8
            <<format_9
            <<format_10;

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Select date format"),
                                         tr("Date Format:"), dateFormats, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        for(int i=0;i<dateFormats.count();i++)
        {
            if(item == dateFormats.at(i))
            {
                cursor.insertText(dateFormats.at(i));
            }
        }
    }

}

void MainWindow::on_setImage_button_6_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTime time = QTime::currentTime();

    QString format_1 = time.toString("h:mm A");
    QString format_2 = time.toString("h:mm:ss A");
    QString format_3 = time.toString("H:mm");
    QString format_4 = time.toString("H:mm:ss");
    QStringList timeFormats;
    timeFormats << format_1
            <<format_2
            <<format_3
            <<format_4;
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Select time format"),
                                         tr("Time Format:"), timeFormats, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        QTime updatedTime = QTime::currentTime();
        format_1 = updatedTime.toString("h:mm A");
        format_2 = updatedTime.toString("h:mm:ss A");
        format_3 = updatedTime.toString("H:mm");
        format_4 = updatedTime.toString("H:mm:ss");
        QStringList updatedList;
        updatedList << format_1
                <<format_2
                <<format_3
                <<format_4;
        for(int i=0;i<timeFormats.count();i++)
        {
            if(item == timeFormats.at(i))
            {
                cursor.insertText(updatedList.at(i));
            }
        }
    }
}

void MainWindow::on_setImage_button_4_clicked()
{
    dim();
    addTable table;
    int x = this->x()+((this->width()-table.width())/2);
    int y = this->y()+((this->height()-table.height())/2);
    table.getLocation(x,y);
    table.getTextEdit(ui->textEdit);
    table.setModal(true);
    table.exec();
    dark->close();
}

void MainWindow::on_lineEdit_2_textChanged(QString word)
{
    findNext(true);

}

void MainWindow::on_textEdit_textChanged()
{
    ui->linesCountLabel->setText(QString::number(ui->textEdit->document()->lineCount()));
    ui->wordsCountLabel->setText(QString::number(countWords()));
    txt.replace(" ","");
    if(txt.isEmpty())
    {
        ui->wordsCountLabel->setText("-");

    }

}

void MainWindow::on_searchNext_clicked()
{
    findNext(false);
}
void MainWindow::findNext(bool start)
{
    if(start)
    {
        ui->textEdit->moveCursor(QTextCursor::Start);
    }
    if(ui->searchBack->isEnabled() == false)
    {
        ui->textEdit->moveCursor(QTextCursor::Start);
    }
    if(matchCase && wholeWordsOnly)
    {
        if( ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindCaseSensitively
                               | QTextDocument::FindWholeWords))
        {
            ui->searchBack->setEnabled(true);
        }
        else
        {
            ui->textEdit->moveCursor(QTextCursor::Start);
            ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindCaseSensitively
                               | QTextDocument::FindWholeWords );
        }
    }
    else if(matchCase)
    {
        if( ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindCaseSensitively))
        {
            ui->searchBack->setEnabled(true);
        }
        else
        {
            ui->textEdit->moveCursor(QTextCursor::Start);
            ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindCaseSensitively);
        }
    }
    else if(wholeWordsOnly)
    {
        if( ui->textEdit->find(ui->lineEdit_2->text(),
                               QTextDocument::FindWholeWords))
        {
            ui->searchBack->setEnabled(true);
        }
        else
        {
            ui->textEdit->moveCursor(QTextCursor::Start);
            ui->textEdit->find(ui->lineEdit_2->text(),
                               QTextDocument::FindWholeWords);
        }
    }
    else
    {
        if( ui->textEdit->find(ui->lineEdit_2->text()))
        {
            ui->searchBack->setEnabled(true);
        }
        else
        {
            ui->textEdit->moveCursor(QTextCursor::Start);
            ui->textEdit->find(ui->lineEdit_2->text());
        }
    }

}

void MainWindow::findBack()
{

    if(wholeWordsOnly && matchCase)
    {
        ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindBackward |
                           QTextDocument::FindCaseSensitively
                           | QTextDocument::FindWholeWords);
    }
    else if(matchCase)
    {
        ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindBackward |
                           QTextDocument::FindCaseSensitively);
    }
    else if(wholeWordsOnly)
    {
        ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindBackward
                           | QTextDocument::FindWholeWords);
    }
    else
    {
        ui->textEdit->find(ui->lineEdit_2->text(),QTextDocument::FindBackward);
    }

}

void MainWindow::on_searchBack_clicked()
{
    findBack();
}

void MainWindow::on_indentDecrease_button_11_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(ui->lineEdit_3->text() != "")
    {
        if(cursor.hasSelection())
        {
            cursor.insertText(ui->lineEdit_3->text());
        }
        findNext(false);
    }

}

void MainWindow::on_indentDecrease_button_12_clicked()
{
    if(ui->lineEdit_3->text() != "")
    {
        findNext(false);
        replaceAll();
    }

}
void  MainWindow::replaceAll()
{
    ui->textEdit->moveCursor(QTextCursor::Start);
    QTextCursor searchCursor = ui->textEdit->textCursor();
    QTextCursor clickedCursor = ui->textEdit->textCursor();
    searchCursor.setPosition(ui->textEdit->document()->begin().position());
    clickedCursor.setPosition(ui->textEdit->document()->begin().position());

    clickedCursor.beginEditBlock();

    while(!searchCursor.isNull() && !searchCursor.atEnd())
    {
        if(matchCase && wholeWordsOnly)
        {
            searchCursor = ui->textEdit->document()->find(ui->lineEdit_2->text(),
                                                          searchCursor,
                                                          QTextDocument::FindCaseSensitively
                                                          | QTextDocument::FindWholeWords);
            searchCursor.insertText(ui->lineEdit_3->text());
        }
        else if(matchCase)
        {
            searchCursor = ui->textEdit->document()->find(ui->lineEdit_2->text(),
                                                          searchCursor,
                                                          QTextDocument::FindCaseSensitively);
            searchCursor.insertText(ui->lineEdit_3->text());
        }

        else if(wholeWordsOnly)
        {
            searchCursor = ui->textEdit->document()->find(ui->lineEdit_2->text(),
                                                          searchCursor,
                                                          QTextDocument::FindWholeWords);
            searchCursor.insertText(ui->lineEdit_3->text());
        }
        else
        {
            searchCursor = ui->textEdit->document()->find(ui->lineEdit_2->text(),
                                                          searchCursor);
            searchCursor.insertText(ui->lineEdit_3->text());
        }
    }
    clickedCursor.endEditBlock();

}

void MainWindow::on_decreaseSpacing_button_5_clicked(bool checked)
{
    if(checked)
    {
        matchCase =true;
        findNext(true);
    }
}

void MainWindow::on_decreaseSpacing_button_4_clicked(bool checked)
{
    if(checked)
    {
        matchCase =false;
        findNext(true);

    }
}


void MainWindow::on_decreaseSpacing_button_6_clicked(bool checked)
{
    if(checked)
    {
        wholeWordsOnly =true;
        findNext(true);

    }
}

void MainWindow::on_decreaseSpacing_button_7_clicked(bool checked)
{
    if(checked)
    {
        wholeWordsOnly =false;
        findNext(true);

    }
}

void MainWindow::on_newFileButton_clicked()
{
    ui->textEdit->setUndoRedoEnabled(false);
    newFile();
    ui->textEdit->setDocumentTitle(ui->lineEdit->text());
    ui->textEdit->setUndoRedoEnabled(true);
}
void  MainWindow::saveFile()
{
    if(checkForSave())
    {
        if(fileName.isEmpty())
        {
          if(fileSaveAs())
            {
              QTextDocumentWriter writer(fileName);
              bool success = writer.write(ui->textEdit->document());
              if (success)
              {
              ui->textEdit->document()->setModified(false);
              ui->label_3->setText("Saved @ "+getTime());
              updateToolTip(fileName);
              ui->lineEdit->setReadOnly(true);
              shortenText(correctName(fileName));
              ui->textEdit->setDocumentTitle(correctName(fileName));
              }

            }
          else
          {
              if(!fileName.isEmpty())
              {
                   Write(fileName);
                   ui->textEdit->document()->setModified(false);
                  ui->label_3->setText("Saved @ "+getTime());
                   updateToolTip(fileName);
                 ui->lineEdit->setReadOnly(true);
                  shortenText(correctName(fileName));
                   ui->textEdit->setDocumentTitle(correctName(fileName));
              }

          }
        }
        else
        {
            qDebug() << "Not empty";
            if(fileExists)
            {
               QTextDocumentWriter writer(fileName);
               bool success = writer.write(ui->textEdit->document());
               if (success)
               ui->textEdit->document()->setModified(false);
              ui->label_3->setText("Saved @ "+getTime());
               updateToolTip(fileName);
               ui->textEdit->setDocumentTitle(correctName(fileName));
            }
            else
            {
                Write(fileName);
                ui->textEdit->document()->setModified(false);
              ui->label_3->setText("Saved @ "+getTime());
               updateToolTip(fileName);
               ui->textEdit->setDocumentTitle(correctName(fileName));
            }

        }
    }
}

bool MainWindow::checkForSave()
{
    if(ui->textEdit->document()->isModified())
    {
        return true;

    }
    else
    {
        return false;

    }


    return true;
}
void MainWindow::newFile()
{
    if(checkForSave())
    {
        ui->textEdit->setDocumentTitle(ui->lineEdit->text());
        dim();
        SaveModifications save;
        save.getWidgets(ui->textEdit,ui->tabWidget,fileName,
                         ui->lineEdit,fileExists,ui->label_3
                         ,reset);
        save.setModal(true);
        int x = this->x()+((this->width()-save.width())/2);
        int y = this->y()+((this->height()-save.height())/2);
        save.getLocation(x,y);
        save.exec();
        dark->close();
    if(reset)
        {

            resetSettings();
            setTextEditDefault();
            ui->textEdit->setDocumentTitle("Untitled");
            ui->textEdit->document()->setModified(false);

        }

    }
    else
    {
        ui->tabWidget->setCurrentIndex(1);
        resetSettings();
        setTextEditDefault();
        ui->textEdit->setDocumentTitle("Untitled");
        ui->tabWidget->setCurrentIndex(0);
        ui->lineEdit->setText("Untitled");
        fileName = "";
        ui->label_3->setText("Not Saved");
        updateToolTip("Not Saved");
        ui->lineEdit->setReadOnly(false);
        ui->textEdit->document()->setModified(false);
    }
}

void MainWindow::on_lineEdit_lostFocus()
{
    if(ui->lineEdit->text() == "")
    {
        ui->lineEdit->setText("Untitled");
    }
     ui->textEdit->setDocumentTitle(ui->lineEdit->text());

}

void MainWindow::on_lineEdit_textEdited(QString )
{

    ui->textEdit->setDocumentTitle(ui->lineEdit->text());

}

void MainWindow::on_toolButton_3_clicked()
{
    this->showMinimized();
}
void MainWindow::Write(QString fileName)
 {
     QFile file(fileName);
     if(!file.open(QFile::WriteOnly | QFile::Text))
     {
         QMessageBox::critical(this,"Error :","Error : File can not be open to write"
                               "\nPlease contact system administrator ...");
         return;
     }
    QTextStream out(&file);
    out << ui->textEdit->document()->toPlainText();
    out.flush();
    file.close();
 }
bool MainWindow::fileSaveAs()
 {
    QString *currentFilter  = new QString;
    fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
   QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation)+"/"+
   ui->textEdit->documentTitle(),tr("Text Documents(*.txt);;"
                           "HTML-Files(*.htm *.html);;"
                           "All Files (*)")
                           ,currentFilter);

    if (fn.isEmpty())
        return false;
    if(*currentFilter == "Text Documents(*.txt)")
    {
        if (!(fn.endsWith(".txt", Qt::CaseInsensitive)))
        fn += ".txt";
        fileName = fn;
        fileExists = false;
        return false;
    }
    else if(*currentFilter =="HTML-Files(*.htm *.html)")
    {
        if (!(fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)))
        fn += ".html";
        fileExists = true;
        fileName = fn;
    }
    else if(*currentFilter =="All Files (*)")
    {
        fileName = fn;
        fileExists = false;
        return false;
    }
    return true;
 }

void MainWindow::on_saveFileButton_clicked()
{
    saveFile();
}
QString MainWindow::correctName(QString path)
 {
    QString correctedName = "";
     for(int i=path.count()-1;i>0;i--)
     {

         if(path.at(i) == '/')
         {
             int j = i+1;

             while(j<path.count())
             {
                 correctedName += path.at(j);
                 j= j+1;
             }
             break;
         }
     }

     QFileInfo mDir(path);
     correctedName.replace("."+mDir.suffix(),"");
     return correctedName;
 }
 void MainWindow::startUp(QString filePath)
 {
     if(!filePath.isEmpty())
     {
        openFile(filePath.replace("\\","/"));
     }
 }

void MainWindow::on_saveAsButton_clicked()
{
    if(fileSaveAs())
      {
        QTextDocumentWriter writer(fileName);
        bool success = writer.write(ui->textEdit->document());
        if (success)
        {

        ui->textEdit->document()->setModified(false);
       ui->label_3->setText("Saved @ "+getTime());
        updateToolTip(fn);
        ui->lineEdit->setReadOnly(true);
        shortenText(correctName(fn));
        ui->textEdit->setDocumentTitle(correctName(fn));

        }
      }
    else
    {
        if(!fn.isEmpty())
        {
             Write(fileName);
             ui->textEdit->document()->setModified(false);
           ui->label_3->setText("Saved @ "+getTime());
             ui->lineEdit->setReadOnly(true);
              updateToolTip(fn);
            shortenText(correctName(fn));
             ui->textEdit->setDocumentTitle(correctName(fn));
        }
    }
}
void MainWindow::resetSettings()
{


    ui->textEdit->clear();
    ui->textEdit->moveCursor(QTextCursor::Start);
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget_2->setCurrentIndex(0);

    ui->fontComboBox->setCurrentFont(set->value("defaultFont","Lucida Grande").value<QFont>());
    ui->horizontalSlider->setValue(set->value("fontSize",10).toInt());
    ui->label_8->setText(QString::number(set->value("fontSize",10).toInt()));
    ui->textEdit->setFont(set->value("defaultFont","Lucida Grande").value<QFont>());
    ui->textEdit->setFontPointSize(set->value("fontSize",10).toInt());
    setFont(set->value("defaultFont","Lucida Grande").value<QFont>());
    textSize(set->value("fontSize",10).toInt());


    ui->boldButton->setChecked(false);
    ui->italicButton->setChecked(false);
    ui->underlineButton->setChecked(false);
    ui->strikeoutButton->setChecked(false);
    ui->subScriptButton->setChecked(false);
    ui->superScriptButton->setChecked(false);

    //Rest the font color
    color  = Qt::black;
    QString col = QString("background : %1 ;border:0px solid %1;").arg(color.name());
    ui->pushButton_25->setStyleSheet(col);
    setFontColor(color.rgb());

     ui->tabWidget_2->setCurrentIndex(1);
   // Reset alignment
    ui->pushButton_9->setChecked(true);

    //Reset the indent & line spacing

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat tbf = cursor.blockFormat();
    tbf.setIndent(0);

    tbf.setLineHeight(0,QTextBlockFormat::LineDistanceHeight); //Only supports under versions higher than 4.7
    ui->label_28->setText("-");
    cursor.setBlockFormat(tbf);

    //Reset word wrapping
    ui->decreaseSpacing_button_2->setChecked(true);

    //Reset bullets & numbering
    //ui->tabWidget_2->setCurrentIndex(2);
    //ui->indentDecrease_button_10->click();


    ui->tabWidget->setCurrentIndex(3);
    //Reset the searching functions
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->decreaseSpacing_button_4->setChecked(true);
    ui->decreaseSpacing_button_7->setChecked(true);

   //Reseting tabs
    ui->tabWidget_2->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);


}

void MainWindow::on_openFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open..."),
          QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                              tr("Text Documents (*.txt);;"
                                                 "All Files (*)"));
    ui->textEdit->setUndoRedoEnabled(false);
    ui->textEdit->setDocumentTitle(ui->lineEdit->text());
    openFile(filePath);

    ui->textEdit->setUndoRedoEnabled(true);
}
 void MainWindow::openFile(QString filePath)
 {


     if(filePath.isEmpty())
     {
         return;
     }

     QFile file(filePath);
     if(!file.open(QFile::ReadOnly | QFile::Text))
     {
            QMessageBox::critical(this,"Error :","Error : File can not be open to read"
                                   "\nPlease contact system administrator ...");
             return;
      }
     else
     {

         resetSettings();
         setTextEditDefault();
         QTextStream in(&file);
         QString text = in.readAll();
         file.close();
         fileExists = false;
         ui->textEdit->moveCursor(QTextCursor::Start);
         setFont(set->value("defaultFont","Lucida Grande").value<QFont>());
         textSize(set->value("fontSize",10).toInt());

         QTextCursor cursor = ui->textEdit->textCursor();
         cursor.insertText(text);
         ui->textEdit->setTextCursor(cursor);

         ui->textEdit->setDocumentTitle(correctName(filePath));
         ui->tabWidget->setCurrentIndex(0);
         ui->lineEdit->setText(correctName(filePath));
         fileName = fn = filePath;

         ui->label_3->setText("File Opened @ "+getTime());
         updateToolTip(filePath);
         ui->lineEdit->setReadOnly(true);
         ui->textEdit->document()->setModified(false);
         QString name = ui->lineEdit->text();
         if(name.count() > 20)
         {
             name.remove(19,name.count()+1-20);
             name.append("...");
             ui->lineEdit->setText(name);
         }

     }
     ui->textEdit->moveCursor(QTextCursor::Start);

 }

void MainWindow::on_pushButton_6_clicked()
{
    dim();
    Settings settings;
    int x = this->x()+((this->width()-settings.width())/2);
    int y = this->y()+((this->height()-settings.height())/2);
    settings.getLocation(x,y);
    bool cancel = false;
    settings.getCancel(cancel);
    settings.setModal(true);
    settings.exec();
    dark->close();
if(!cancel)
    {

    ui->frame_4->setStyleSheet(QString("background : %1;"
                                       "QLabel{"
                                       "background : none;"
                                       "color : white;"
                                       "}"
                                       )
                               .arg(set->value("themeColor","#272727")
                                    .toString()));
    ui->lineEdit->setStyleSheet(QString("color : white;"
                                "background : %1;")
                                .arg(set->value("themeColor","#272727")
                                .toString()));
    ui->textEdit->setAcceptRichText(set->value("keepFormat",false).toBool());
    }

}
QString MainWindow::getTime()
{
    QTime time = QTime::currentTime();
    QString now = time.toString("h:mm A");
    return now;
}


void MainWindow::on_toPdf_button_clicked()
{
    //to PDF
    QString pdfPath = QFileDialog::getSaveFileName(this, "Export PDF",
    QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation)+
    "/"+ui->textEdit->documentTitle(),"*.pdf");

    if (!pdfPath.isEmpty())
    {
        QFile file(pdfPath);
        if(file.open(QFile::Append))
            {
           if (QFileInfo(pdfPath).suffix().isEmpty())
           pdfPath.append(".pdf");
           QPrinter printer(QPrinter::HighResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName(pdfPath);
           ui->textEdit->document()->print(&printer);
           ui->label_3->setText("Saved @ "+getTime());
           updateToolTip(pdfPath);
           ui->textEdit->document()->setModified(false);
           shortenText(correctName(pdfPath));
           ui->textEdit->setDocumentTitle(correctName(pdfPath));

            }

        else
            {
             QMessageBox::critical(this,"Error :","The document is used by another "
             "program.\nThe data can not be written into the document."
                 "\nPlease close that program and try again.");
            }
     }

}
 void MainWindow::updateToolTip(QString toolTip)
 {
     ui->label_3->setToolTip(toolTip);
 }
void MainWindow::dim()
{
    dark->getGeometry(this->geometry().x(),
                     this->geometry().y(),
                     this->width(),
                     this->height());
    dark->updateGeometry();
    dark->show();
}
  void MainWindow::dragEnterEvent(QDragEnterEvent *event)
  {
      event->acceptProposedAction();

  }

  void MainWindow::dragMoveEvent(QDragMoveEvent *event)
  {
      event->acceptProposedAction();
  }

  void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
  {
      event->accept();
  }

  void MainWindow::dropEvent(QDropEvent *event)
  {
    const QMimeData *mimeData = event->mimeData();
    QList<QUrl> urls = mimeData->urls();
    if(!urls.isEmpty())
    {

        setTextEditDefault();
        openFile(urls.at(0).toString().replace("file:///",""));

    }
  }


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 3)
    {
        ui->lineEdit_2->setFocus(Qt::MouseFocusReason);
    }
    else
    {
        ui->textEdit->setFocus(Qt::MouseFocusReason);
    }
}
bool MainWindow::eventFilter( QObject *dist, QEvent *event )
{
  if( dist == ui->frame_5 && event->type() == QEvent::MouseButtonPress)
  {
      if(checkDrag==true && this->isMaximized() == false)
      {
         drag = true;
          mousex =  QCursor::pos().x() - this->x();
          mousey =  QCursor::pos().y() - this->y();
      }
           return true;
  }
  if( dist == ui->frame_5 && event->type() == QEvent::MouseMove)
  {
      if(drag )
      {

          this->setGeometry(QRect(QCursor::pos().x()-mousex , QCursor::pos().y()-mousey ,
                                  this->width(),this->height() ));

          }
      return true;

      }

  if( dist == ui->frame_5 && event->type() == QEvent::MouseButtonRelease)
  {
      drag = false;
      return true;
  }
  if( dist == ui->frame_5 && event->type() == QEvent::MouseButtonDblClick)
  {
     setWindowState();
     return true;
  }

  return false;
}

void MainWindow::on_pushButton_8_clicked()
{
    try{
        QUrl url("file:///"+QApplication::applicationDirPath()
                       +"/CutePad-help.pdf");
       QDesktopServices::openUrl(url);
    }
    catch(QString error)
    {
        QMessageBox::critical(this,"Error :",error);
    }
}
void MainWindow::setTextEditDefault(){


   ui->textEdit->setHtml(QString(
           "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0"
           "//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
           "<html><head><meta name=\"qrichtext\" content=\"1\" />"
           "<style type=\"text/css\">"
           "p, li { white-space: pre-wrap; }"
           "</style></head><body style=\" font-family:'%1';"
           "font-size:%2pt; font-weight:400; font-style:normal;\">"
           "</body></html>").arg(
                  set->value("defaultFont","Lucida Grande").toString()).arg(
                          set->value("fontSize",10).toInt())
                         );
}
void MainWindow::shortenText(QString name)
{
    if(name.count() > 20)
    {
        name.remove(19,name.count()+1-20);
        name.append("...");
        ui->lineEdit->setText(name);
    }
    else{
         ui->lineEdit->setText(name);
    }
}

void MainWindow::on_pushButton_7_clicked()
{


//    a.setModal(true);
//    a.exec();
    dim();
    About a;
    int x = this->x()+((this->width()-a.width())/2);
    int y = this->y()+((this->height()-a.height())/2);
    a.getLocation(x,y);
    a.setModal(true);
    a.exec();
    dark->close();

}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_7);
}
