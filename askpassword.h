#ifndef ASKPASSWORD_H
#define ASKPASSWORD_H

#include <QtWidgets/QDialog>
#include <QtGui>
#include <QtWidgets/QMessageBox>

namespace Ui {
class AskPassword;
}

class AskPassword : public QDialog
{
    Q_OBJECT
    
public:
    AskPassword(QWidget *parent = 0, QString pass = NULL);
    ~AskPassword();
    
private:
    Ui::AskPassword *ui;
    QString strPassword ;

private slots:

    void on_okButton_clicked() ;
    void on_cancelButton_clicked() ;

    void on_lineEdit_textChanged() ;
};

#endif // ASKPASSWORD_H
