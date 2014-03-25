#ifndef DOTASK_H
#define DOTASK_H
#include <QtCore>
#include <QtGui>

#include <QObject>

class DoTask : public QObject
{
    Q_OBJECT
public:
    explicit DoTask(QObject *parent = 0);
    void start(QDialog *d);
    QDialog *dialog;
    QTimer *timer;


public slots:
    void startingWindow();
    void closingWindow();
};

#endif // DOTASK_H
