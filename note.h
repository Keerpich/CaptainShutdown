#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QtGui>
#include <QMessageBox>

#include <ostream>
#include <istream>

using namespace std;

#define BEFORE_SHUT 0
#define AT_TIME 1

class Note
{
public:
    Note(QWidget *parent2 = 0);

    Note operator= (Note& other) ;

public:
    bool timeExpired (QDateTime tmp) ;
    void displayNote () ;

    int getMode() const ;
    bool getTrayDisplay () const ;
    bool getWindowDisplay () const ;
    QDateTime getTime() const;
    QString getTitle () const;
    QString getDetails () const;

    void setTime (QDateTime tocop);
    void setTime (int h, int m, int s);
    void setMode (int Mo) ;
    void setTrayDisplay (bool TDMo) ;
    void setWindowDisplay (bool WDMo) ;
    void setTitle (QString T) ;
    void setDetails (QString D) ;

private:
    bool checkAgainstTime (const QDateTime checker) ;
    bool elapseTime () ;

    QWidget *parent ;

    QDateTime time;

    qint64 toAdd;

    int iMode ;
    bool bTrayDisplay ;
    bool bWindowDisplay ;

    QString strTitle ;
    QString strDetails ;

public:

    friend std::ostream& operator<< (ostream& out, const Note &note);
    friend std::istream& operator>> (istream& in,Note &note);



};

#endif // NOTE_H
