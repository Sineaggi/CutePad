/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "dark.h"
#include "ui_dark.h"

Dark::Dark(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dark)
{
    ui->setupUi(this);


}

Dark::~Dark()
{

    delete ui;
}
 void Dark::getGeometry(int x,int y,int width,int height)
 {
     this->setWindowFlags(Qt::SplashScreen);
     this->setGeometry(QRect(x,y,width,height));

 }
