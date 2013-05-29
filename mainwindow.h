#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QDateTime>

#include <stdio.h>
//#include <unistd.h>

#include "setpassword.h"
#include "askpassword.h"
#include "addnote.h"
#include "note.h"
#include "getlinuxpass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getSdState () ;

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *event) ;

private slots:

    void on_sLineEdit_focussed(bool focus) ;
    void on_mLineEdit_focussed(bool focus) ;
    void on_hLineEdit_focussed(bool focus) ;

    void on_sLineEdit_editingFinished() ;
    void on_mLineEdit_editingFinished() ;
    void on_hLineEdit_editingFinished() ;

    void lineChanged() ;
    void updateTime () ;
    void toQuit () ;

    void on_okButton_clicked() ;
    void on_abButton_clicked() ;
    void on_exitButton_clicked() ;

    void on_resetAction_triggered() ;
    void on_exitAction_triggered() ;

    void on_aboutCptAction_triggered() ;
    void on_aboutQtAction_triggered() ;

    void on_setPAction_triggered() ;
    void on_editPAction_triggered() ;
    void on_removePAction_triggered() ;

    void on_addNoteAction_triggered() ;

    void on_taskManagerAction_clicked() ;

    void trayIconClicked (QSystemTrayIcon::ActivationReason) ;

public slots:
    void slAskAccepted () ;
    void slAskRejcted () ;

    void setPAction_correct() ;
    void setPAction_incorrect () ;
    void setPAction_register(const QString &pass) ;

private:

    std::string IntToString (int IntValue) ;
    int GetIntVal (std::string StrConvert) ;
    void ClearAndAdd (QLineEdit *lineEdit, QString &text) ;
    void displayLcd() ;

    void reqLnxPass() ;
    bool reqPassword() ;
    void passSetup();
    void passSet() ;

    void createActions() ;
    void createTrayIcon () ;
    void setIcon () ;
    void createMenus() ;

    std::map<std::string, Note> Notes ;

    QSystemTrayIcon *trayIcon ;
    QMenu *trayIconMenu ;

    QAction *open ;
    QAction *exit ;

    QString setPassword ;
    QString toCheckPass ;
    QString linuxPass ;

    std::string strTimer ;

    QTimer *timer ;

    QDateTime time;

    bool bReqPassword ;
    bool bSdEnabled ;

    int iSeconds ;
    int iMinutes ;
    int iHours ;
    int iShowedSeconds ;
    int iShowedMinutes ;
    int iShowedHours ;

    QMenu *optionsMenu ;
    QMenu *helpMenu ;

    QAction *resetAction ;
    QAction *aboutAction ;
    QAction *exitAction ;

    QSystemTrayIcon *mTray ;
};

#endif // MAINWINDOW_H
