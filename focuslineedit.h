#ifndef FOCUSLINEEDIT_H
#define FOCUSLINEEDIT_H

#include <QObject>
#include <QLineEdit>

class FocusLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit FocusLineEdit(QWidget *parent = 0);
    ~FocusLineEdit() ;
    
signals:
    void focussed (bool hasFocus) ;

public slots:

protected:
    virtual void focusInEvent(QFocusEvent *e) ;
    virtual void focusOutEvent(QFocusEvent *e) ;

};

#endif // FOCUSLINEEDIT_H
