#ifndef GETLINUXPASS_H
#define GETLINUXPASS_H

#include <QDialog>

namespace Ui {
class getLinuxPass;
}

class getLinuxPass : public QDialog
{
    Q_OBJECT
    
public:
    explicit getLinuxPass(QWidget *parent = 0, QString *pass = NULL);
    ~getLinuxPass();
    
private:
    Ui::getLinuxPass *ui;

    QString *strPassword ;

private slots:

    void on_okButton_clicked();
    void on_cancelButton_clicked();

    void on_passwordLineEdit_textChanged();
};

#endif // GETLINUXPASS_H
