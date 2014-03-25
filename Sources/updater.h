/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef UPDATER_H
#define UPDATER_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class Updater;
}

class Updater : public QDialog
{
    Q_OBJECT

public:
    explicit Updater(QWidget *parent = 0);
    ~Updater();
    void getInformation(float CurrVersion,
                   float NewVersion,
                   QString includedFeatures,
                   QString link);
    QString Versionlink;
private:
    Ui::Updater *ui;

private slots:
    void on_checkBox_toggled(bool checked);
    void on_pushButton_clicked();
    void on_cancelButton_clicked();
};

#endif // UPDATER_H
