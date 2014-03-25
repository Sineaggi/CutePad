/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef SAVEMODIFICATIONS_H
#define SAVEMODIFICATIONS_H
#include <QtGui>
#include <QtCore>

#include <QDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
    class SaveModifications;
}

class SaveModifications : public QDialog
{
    Q_OBJECT
protected:
     bool eventFilter( QObject *dist, QEvent *event );
public:
    explicit SaveModifications(QWidget *parent = 0);
    ~SaveModifications();
    QTimer *timer;
    bool fileExists;
    QTextEdit *textEdit;
    QTabWidget *tabWidget;
    QString *fileName;
    bool *reset;
    QLineEdit *lineEdit;
    QLabel *label;
    void doWork(bool stat);
    void getWidgets(QTextEdit *editor,QTabWidget *tab,
                    QString &file,QLineEdit *lEdit
                    ,bool fExists,QLabel *mlabel,bool &RESET
                    );
    bool save();
    bool fileSaveAs();
    void getLocation(int x,int y);
    bool checkDrag;
    bool drag;
    int mousex,mousey;
private:
    Ui::SaveModifications *ui;
    void Write(QString *fileName);


private slots:

    void startingWindow();
    void closingWindow();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // SAVEMODIFICATIONS_H
