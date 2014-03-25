/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef ADDTABLE_H
#define ADDTABLE_H
#include <QtCore>
#include <QtGui>

#include <QDialog>

namespace Ui {
    class addTable;
}

class addTable : public QDialog
{
    Q_OBJECT
protected:
     bool eventFilter( QObject *dist, QEvent *event );
public:
    explicit addTable(QWidget *parent = 0);
    ~addTable();
    void startUp();
     void getLocation(int x,int y);
     QTimer *timer;
     QTextTableFormat format;
     QColor color;
     QColor border;
     Qt::Alignment alignment;
     QTextEdit *textEdit;
     void getTextEdit(QTextEdit *text);
     void setTable(int rows,int columns,int spacing,int padding,QColor background,
                   QColor border,Qt::Alignment alignment);
     bool checkDrag;
     bool drag;
     int mousex,mousey;
private:
    Ui::addTable *ui;

private slots:
    void on_toolButton_clicked();
    void startingWindow();
    void closingWindow();
    void on_insertButton_clicked();
    void on_cancelButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_spinBox_4_valueChanged(int );
    void on_spinBox_3_valueChanged(int );
    void on_spinBox_2_valueChanged(int );
    void on_spinBox_valueChanged(int );
};

#endif // ADDTABLE_H
