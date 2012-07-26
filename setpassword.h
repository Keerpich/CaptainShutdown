#ifndef SETPASSWORD_H
#define SETPASSWORD_H

#include <QDialog>

#include "mainwindow.h"

class MainWindow ;

namespace Ui {
class SetPassword;
}

class SetPassword : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetPassword(QWidget *parent = 0);
    ~SetPassword();
    
private:
    Ui::SetPassword *ui;

protected:
    void closeEvent(QCloseEvent *event) ;

private:
    void checkBut () ;

private slots:
    void on_okButton_clicked() ;
    void on_cancelButton_clicked() ;

    void on_pass1_textChanged() ;
    void on_pass2_textChanged() ;
};

#endif // SETPASSWORD_H
