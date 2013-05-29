    #include "dateandtime.h"
#include "ui_dateandtime.h"

DateAndTime::DateAndTime(QWidget *parent, QDateTime *perim) :
    QDialog(parent),
    ui(new Ui::DateAndTime)
{
    ui->setupUi(this);
    retDAT = perim;
}

DateAndTime::~DateAndTime()
{
    delete ui;
}

void DateAndTime::on_timeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateandtime = dateTime ;
}

void DateAndTime::on_okButton_clicked()
{
    *retDAT = dateandtime;
    this->close();
}

void DateAndTime::on_cancelButton_clicked()
{
    this->close();
}
