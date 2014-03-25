/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef CHECKUPDATES_H
#define CHECKUPDATES_H

#include <QObject>
// FIXME
// #include <QHttp>
#include <QtCore>
#include <QMessageBox>
#include <QtGui>
#include "updater.h"
class checkUpdates : public QObject
{
    Q_OBJECT
public:
    explicit checkUpdates(QObject *parent = 0);
    void doCheck();
    void getParent(QWidget *parent);
    QWidget *widget;

signals:

public slots:
    void stateChanged ( int state );
    // FIXME
    // void responseHeaderReceived ( const QHttpResponseHeader & resp );
    void requestFinished ( int id, bool error );
private:
    // FIXME
    // QHttp *http;
};

#endif // CHECKUPDATES_H
