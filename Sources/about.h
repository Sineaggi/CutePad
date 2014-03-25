/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class About;
}

class About : public QDialog
{
    Q_OBJECT
protected:
    void mouseReleaseEvent(QMouseEvent *);
public:
    explicit About(QWidget *parent = 0);
    ~About();
    QTimer *timer;
    bool checkDrag;
    bool drag;
    int mousex,mousey;
    void getLocation(int x,int y);
private:
    Ui::About *ui;

private slots:
    void on_toolButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void startingWindow();
    void closingWindow();
};

#endif // ABOUT_H
