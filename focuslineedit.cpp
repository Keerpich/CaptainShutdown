#include "focuslineedit.h"

FocusLineEdit::FocusLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

FocusLineEdit::~FocusLineEdit()
{
}

void FocusLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e) ;
    emit(focussed(true)) ;
}

void FocusLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e) ;
    emit(focussed(false)) ;
}
