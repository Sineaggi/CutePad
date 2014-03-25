/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "updater.h"
#include "ui_updater.h"

Updater::Updater(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Updater)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

}

Updater::~Updater()
{

    delete ui;
}

void Updater::on_cancelButton_clicked()
{
    this->close();
}
void Updater::getInformation(float CurrVersion,
               float NewVersion,
               QString includedFeatures,
               QString link)
{
    ui->currVersionLabel->setText(QString::number(CurrVersion));
    ui->newVersionLable->setText(QString::number(NewVersion));
    ui->plainTextEdit->appendPlainText(includedFeatures);
    Versionlink = link;
}

void Updater::on_pushButton_clicked()
{
  QDesktopServices::openUrl(QUrl(Versionlink, QUrl::TolerantMode));
  this->close();
}

void Updater::on_checkBox_toggled(bool checked)
{
    QSettings set(QSettings::IniFormat, QSettings::UserScope,
                           "Serandibosft", "CutePad");
    if(checked)
    {
      set.setValue("checkUpdates",false);
    }
    else
    {
      set.setValue("checkUpdates",true);
    }
}
