/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef SETTINGS_H
#define SETTINGS_H
#include <QtCore>
#include <QDialog>

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QTimer *timer;
    bool checkDrag;
    bool drag;
    int mousex,mousey;
    void getLocation(int x,int y);
    void getCancel(bool &cancel);
    void applyChanges();
    QSettings *set;


protected:
    bool eventFilter( QObject *dist, QEvent *event );
private:
    Ui::Settings *ui;
    void setProperties();
    bool *isCancel;
public slots:
    void startingWindow();
    void closingWindow();

private slots:

    void on_pushButton_4_clicked();
    void on_pushButton_26_clicked(bool checked);
    void on_pushButton_27_clicked(bool checked);
    void on_pushButton_25_clicked(bool checked);
    void on_pushButton_24_clicked(bool checked);
    void on_pushButton_23_clicked(bool checked);
    void on_pushButton_22_clicked(bool checked);
    void on_pushButton_21_clicked(bool checked);
    void on_pushButton_20_clicked(bool checked);
    void on_pushButton_19_clicked(bool checked);
    void on_pushButton_18_clicked(bool checked);
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_toolButton_clicked();
};

#endif // SETTINGS_H
