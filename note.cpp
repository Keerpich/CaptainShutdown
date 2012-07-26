#include "note.h"

Note::Note (QWidget *parent2) :
    parent(parent2)
{
}

bool Note::checkAgainstTime(const int H, const int M, const int S)
{
    return (H == iHours && M == iMinutes && S == iSeconds) ;
}

bool Note::elapseTime()
{
    if (iSeconds == 0 && iMinutes == 0 && iHours == 0)
    {
        return true ;
    }
    else if (iSeconds == 0)
    {
        if (iMinutes == 0)
        {
            iHours-- ;
            iMinutes = 59 ;
            iSeconds = 60 ;
        }
        else
        {
            iMinutes-- ;
            iSeconds = 60 ;
        }
    }

    iSeconds-- ;

    return false ;
}

const int Note::getMode()
{
    return iMode ;
}

void Note::setH(int H)
{
    iHours = H ;
}

void Note::setM(int M)
{
    iMinutes = M ;
}

void Note::setS(int S)
{
    iSeconds = S ;
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

bool Note::timeExpired(int H, int M, int S)
{
    if (iMode == BEFORE_SHUT)
    {
        if (checkAgainstTime(H, M, S))
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

const int Note::getH()
{
    return iHours ;
}

const int Note::getM()
{
    return iMinutes ;
}

const int Note::getS()
{
    return iSeconds ;
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
    this->setH(other.getH()) ;
    this->setM(other.getM()) ;
    this->setS(other.getS()) ;
    this->setMode(other.getMode()) ;
    this->setTitle(other.getTitle()) ;
    this->setDetails(other.getDetails()) ;
    this->setTrayDisplay(other.getTrayDisplay()) ;
    this->setWindowDisplay(other.getWindowDisplay()) ;

    return *this ;
}

const bool Note::getTrayDisplay()
{
    return bTrayDisplay ;
}

const bool Note::getWindowDisplay()
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
