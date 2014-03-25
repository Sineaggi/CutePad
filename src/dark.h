/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef DARK_H
#define DARK_H
#include <QtGui>
#include <QtCore>
#include <QDialog>

namespace Ui {
    class Dark;
}

class Dark : public QDialog
{
    Q_OBJECT

public:
    explicit Dark(QWidget *parent = 0);
    ~Dark();
    void getGeometry(int x,int y,int width,int height);

private:
    Ui::Dark *ui;

};

#endif // DARK_H
