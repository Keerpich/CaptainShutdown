#include "note.h"

Note::Note (QWidget *parent2) :
    parent(parent2)
{
}

bool Note::checkAgainstTime(const QDateTime checker)
{
    return (!(QDateTime::currentDateTime().addSecs(toAdd) < checker)) ;
}

bool Note::elapseTime()
{

    if (!(time > QDateTime::currentDateTime()))
        return true;

    return false;
}


int Note::getMode() const
{
    return iMode ;
}


void Note::setTime(QDateTime tocop)
{
    time = tocop ;
}

void Note::setTime(int hour,int min, int sec)
{
    time = QDateTime::currentDateTime().addSecs(hour + min + sec);
    toAdd = hour + min + sec;
}

void Note::setMode(int Mo)
{
    iMode = Mo ;
}

void Note::setTitle (QString T)
{
    strTitle = T ;
}

void Note::setDetails (QString D)
{
    strDetails = D ;
}

void Note::displayNote()
{
    QMessageBox::information(parent ,strTitle,
                             strDetails,
                                QMessageBox::Ok) ;
}

bool Note::timeExpired(QDateTime tmp)
{
    if (iMode == BEFORE_SHUT)
    {
        if (checkAgainstTime(tmp))
        {
            return true ;
        }
    }
    else
    {
        if (elapseTime())
        {
            return true ;
        }
    }

    return false ;
}


const QDateTime Note::getTime()
{
    return time;
}

const QString Note::getDetails()
{
    return strDetails ;
}

const QString Note::getTitle()
{
    return strTitle ;
}

Note Note::operator =(Note &other)
{
    this->setTime(other.getTime());
    this->setMode(other.getMode()) ;
    this->setTitle(other.getTitle()) ;
    this->setDetails(other.getDetails()) ;
    this->setTrayDisplay(other.getTrayDisplay()) ;
    this->setWindowDisplay(other.getWindowDisplay()) ;

    return *this ;
}

bool Note::getTrayDisplay() const
{
    return bTrayDisplay ;
}

bool Note::getWindowDisplay() const
{
    return bWindowDisplay ;
}

void Note::setTrayDisplay(bool TDMo)
{
    bTrayDisplay = TDMo ;
}

void Note::setWindowDisplay(bool WDMo)
{
    bWindowDisplay = WDMo ;
}
