#ifndef DATEANDTIME_H
#define DATEANDTIME_H

#include <QtWidgets/QDialog>
#include <QtGui>

namespace Ui
{
    class DateAndTime;
}

class DateAndTime : public QDialog
{
    Q_OBJECT
public:
    explicit DateAndTime(QWidget *parent = 0, QDateTime* retDAT = NULL);
    ~DateAndTime();

private:
    Ui::DateAndTime *ui;
    QDateTime dateandtime;
    QDateTime *retDAT;
    
signals:
    
public slots:
    
private slots:
    void on_timeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // DATEANDTIME_H
