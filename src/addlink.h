/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef ADDLINK_H
#define ADDLINK_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class addLink;
}

class addLink : public QDialog
{
    Q_OBJECT
protected:
     bool eventFilter( QObject *dist, QEvent *event );
public:
    explicit addLink(QWidget *parent = 0);
    ~addLink();
    void getLocation(int x,int y);
     QTextEdit *edit;
     void getTextEdit(QTextEdit *textEdit);
     QTimer *timer;
     bool checkDrag;
     bool drag;
     int mousex,mousey;

private:
    Ui::addLink *ui;

private slots:


    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_toggled(bool checked);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void startingWindow();
    void closingWindow();
   void on_toolButton_clicked();
};

#endif // ADDLINK_H
