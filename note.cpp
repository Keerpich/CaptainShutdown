#include "note.h"

#include <QDebug>

Note::Note (QWidget *parent2) :
    parent(parent2)
{
    soundEn = false;
	bWindowDisplay = false;
	bTrayDisplay = false;
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
    if(isSound())
    {
        playWav();
    }

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


QDateTime Note::getTime() const
{
    return time;
}

QString Note::getDetails() const
{
    return strDetails ;
}

QString Note::getTitle() const
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
	this->setSound(other.isSound());

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

std::ostream& operator<< (std::ostream& out, const Note& note)
{
    out << note.time.toString().toStdString() << endl;
	out << note.iMode << endl;
    out << note.strDetails.toStdString() << endl;
    out << note.strDetails.toStdString() << endl;
    out << note.bTrayDisplay << endl ;
    out << note.bWindowDisplay << endl;
    out << note.soundEn << endl;

    return out;
}

std::istream& operator>> (std::istream& in, Note& note)
{
    string title, date, details;
    string ext;

    getline (in, ext);
    getline (in, date); note.time = QDateTime::fromString(QString::fromUtf8(date.c_str()));
    in >> note.iMode ; getline (in, ext);
    getline(in, title); note.strTitle = QString::fromUtf8(title.c_str());
    getline(in, details); note.strDetails = QString::fromUtf8(details.c_str());
    in >> note.bTrayDisplay;
    in >> note.bWindowDisplay;
    in >> note.soundEn;

    return in;

}

void Note::playWav()
{
    QSound::play("bell.wav");
}

void Note::setSound(bool set)
{
    soundEn = set;
}

bool Note::isSound() const
{
    return soundEn;
}
