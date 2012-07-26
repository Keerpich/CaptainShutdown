#include <QtGui>

#include "setpassword.h"
#include "ui_setpassword.h"

extern MainWindow w ;

SetPassword::SetPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPassword)
{
    ui->setupUi(this);

    ui->pass1->setEchoMode(QLineEdit::Password) ;
    ui->pass2->setEchoMode(QLineEdit::Password) ;

    connect (ui->pass1, SIGNAL (textEdited(const QString &)),
             parent, SLOT (setPAction_register(const QString &))) ;

    connect (this, SIGNAL (accepted()), parent, SLOT (setPAction_correct())) ;
    connect (this, SIGNAL (rejected()), parent, SLOT (setPAction_incorrect())) ;
}

SetPassword::~SetPassword()
{
    delete ui;
}

void SetPassword::on_cancelButton_clicked()
{
    ui->pass1->clear();
    ui->pass2->clear();

    reject() ;
}

void SetPassword::checkBut()
{
    ui->okButton->setEnabled((!(ui->pass1->text().isEmpty()))
                                 && (!(ui->pass2->text().isEmpty())));
}

void SetPassword::on_pass1_textChanged()
{
    checkBut() ;
}

void SetPassword::on_pass2_textChanged()
{
    checkBut() ;
}

void SetPassword::on_okButton_clicked()
{
    if (ui->pass1->text() == ui->pass2->text())
    {
        accept() ;
    }

    else
    {
        QMessageBox::critical (this, tr("Error"),
                               tr("Passwords don't match"), QMessageBox::Ok) ;
        ui->pass1->clear();
        ui->pass2->clear();
    }
}

void SetPassword::closeEvent(QCloseEvent *event)
{
    ui->pass1->clear();
    ui->pass2->clear();

    reject() ;
}

