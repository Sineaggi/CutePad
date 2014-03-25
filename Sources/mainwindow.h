/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QtGui>
#include "addLink.h"
#include "savemodifications.h"
#include <QMainWindow>
#include "addtable.h"
#include "dark.h"
#include "settings.h"
#include "checkupdates.h"
#include "about.h"

#include <QGraphicsOpacityEffect>
#include <QPrinter>
#include <QDesktopWidget>
#include <QMenu>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    bool eventFilter( QObject *dist, QEvent *event );
    virtual void closeEvent(QCloseEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QSettings *set;
    QString fn;
    bool reset;
    bool fileExists;
    QString resetDoc;
    bool wholeWordsOnly;
    bool matchCase;
    QTextCursor clickedCursor;
    QTextCursor clickedHighlightCursor;
    QTextDocument *searchDoc;
    QString fileName;
    QString txt;
    int words;
    QColor color;
    QFont font;
    QTimer *timer;
    int borderWidth;
    int mousex,mousey;
    bool checkDrag;
    bool drag;
    Dark *dark;


   void startUp(QString filePath);

private:


    Ui::MainWindow *ui;
    bool fileSaveAs();
    void setWindowState();
    void Write(QString fileName);
    void saveFile();
    void newFile();

    void shortenText(QString name);
    void setTextEditDefault();
    bool checkForSave();
    void setSettings();
    void check();
    void centerForm();
    void updateToolTip(QString toolTip);
    QString getTime();
    void setupActions();
    void replaceAll();
    void findBack();
    void findNext(bool start);
    void setUserName();
    void dim();
    void openFile(QString filePath);
    void resetSettings();
    void setFrameless();
    int countWords();
    void pickColor();
    QString correctName(QString path);
    //Do the text modifications on commands of buttons
    void setBold(bool);
    void setItalic(bool);
    void setunderLine(bool);
    void setStrikeOut(bool);
    void setSuperScript(bool);
    void setSubScript(bool);

    void setMargin(int margin);
    void textSize(int p);
    void setFontColor(QRgb RGB);
    void setFont(QFont font);

    void bulletsNumbering(int index);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    //Automatically change the stats of button according to the current font
    void fontChanged(const QFont &f);
    void currentCharFormatChanged(const QTextCharFormat &format);
    void alignmentChanged(Qt::Alignment a);

    QGraphicsOpacityEffect *opacity;
private slots:

    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_toPdf_button_clicked();
    void on_pushButton_6_clicked();
    void on_openFileButton_clicked();
    void on_saveAsButton_clicked();
    void on_saveFileButton_clicked();
    void on_toolButton_3_clicked();
    void on_lineEdit_textEdited(QString );
    void on_lineEdit_lostFocus();
    void on_newFileButton_clicked();
    void on_decreaseSpacing_button_7_clicked(bool checked);
    void on_decreaseSpacing_button_6_clicked(bool checked);
    void on_decreaseSpacing_button_4_clicked(bool checked);
    void on_decreaseSpacing_button_5_clicked(bool checked);
    void on_indentDecrease_button_12_clicked();
    void on_indentDecrease_button_11_clicked();
    void on_searchBack_clicked();
    void on_searchNext_clicked();
    void on_lineEdit_2_textChanged(QString );

    void on_setImage_button_4_clicked();
    void on_setImage_button_6_clicked();
    void on_setImage_button_5_clicked();
    void on_setImage_button_2_clicked();
    void on_setImage_button_clicked();

    void on_toolButton_2_clicked();

    void on_indentDecrease_button_10_clicked();
    void on_indentDecrease_button_9_clicked();
    void on_indentDecrease_button_8_clicked();
    void on_indentDecrease_button_7_clicked();
    void on_indentDecrease_button_6_clicked();
    void on_indentDecrease_button_5_clicked();
    void on_indentDecrease_button_4_clicked();
    void on_indentDecrease_button_3_clicked();
    void on_indentDecrease_button_2_clicked();
    void on_decreaseSpacing_button_3_toggled(bool checked);
    void on_decreaseSpacing_button_2_toggled(bool checked);
    void on_increaseSpacing_button_clicked();
    void on_decreaseSpacing_button_clicked();
    void on_indentIncrease_button_clicked();
    void on_indentDecrease_button_clicked();
    void on_textEdit_cursorPositionChanged();
    void on_pushButton_9_clicked(bool checked);
    void on_pushButton_28_clicked(bool checked);
    void on_pushButton_13_clicked(bool checked);
    void on_pushButton_12_clicked(bool checked);
    void on_horizontalSlider_actionTriggered(int action);
    void on_superScriptButton_toggled(bool checked);
    void on_subScriptButton_toggled(bool checked);
    void on_fontComboBox_activated(QString );
    void on_fontComboBox_currentFontChanged(QFont f);
    void on_pushButton_25_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_10_clicked();
    void startingWindow();
    void closingWindow();
    void on_strikeoutButton_clicked(bool checked);
    void on_underlineButton_clicked(bool checked);
    void on_italicButton_clicked(bool checked);
    void on_textEdit_currentCharFormatChanged(QTextCharFormat format);
    void on_boldButton_clicked(bool checked);
    void on_pushButton_24_clicked();
    void on_toolButton_clicked();
    void on_textEdit_textChanged();
    void print();
    void printPreview();
    void printPreview(QPrinter *);


signals:

    void sliderToMaximum();
    void sliderToMinimum();
};

#endif // MAINWINDOW_H
