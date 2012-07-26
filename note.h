#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QtGui>
#include <QMessageBox>

#define BEFORE_SHUT 0
#define AT_TIME 1

class Note
{
public:
    Note(QWidget *parent2 = 0);

    Note operator= (Note& other) ;

public:
    bool timeExpired (int H, int M, int S) ;
    void displayNote () ;

    const int getMode () ;
    const bool getTrayDisplay () ;
    const bool getWindowDisplay () ;
    const int getH () ;
    const int getM () ;
    const int getS () ;
    const QString getTitle () ;
    const QString getDetails () ;

    void setH (int H) ;
    void setM (int M) ;
    void setS (int S) ;
    void setMode (int Mo) ;
    void setTrayDisplay (bool TDMo) ;
    void setWindowDisplay (bool WDMo) ;
    void setTitle (QString T) ;
    void setDetails (QString D) ;

private:
    bool checkAgainstTime (const int H, const int M, const int S) ;
    bool elapseTime () ;

    QWidget *parent ;

    int iHours ;
    int iMinutes ;
    int iSeconds ;

    int iMode ;
    bool bTrayDisplay ;
    bool bWindowDisplay ;

    QString strTitle ;
    QString strDetails ;

};

#endif // NOTE_H
