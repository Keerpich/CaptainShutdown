#ifndef ADDNOTE_H
#define ADDNOTE_H

#include <QtWidgets/QDialog>
#include <QLineEdit>
#include <QtGui>

#include <map>
#include <string>

#include "note.h"
#include "dateandtime.h"

class Note ;

namespace Ui {
class AddNote;
}

class AddNote : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddNote(QWidget *parent = 0, std::map<std::string, Note> *nNote = NULL,int sdState = 0) ;
    ~AddNote();
    
private:
    Ui::AddNote *ui;
    Note newNote ;
    QDateTime noteDate;

    std::map<std::string, Note> *vNote;

    void enableOK () ;
    void repopCombo () ;
    bool nameInNotes (QString qstrText) ;

    std::string IntToString (int IntValue) ;
    int GetIntVal (std::string StrConvert) ;

private slots:
    void on_trayCheckBox_stateChanged () ;
    void on_windowCheckBox_stateChanged () ;

    void on_titleLineEdit_editingFinished () ;
    void on_detailsTextEdit_textChanged () ;

    void on_hLineEdit_editingFinished () ;
    void on_mLineEdit_editingFinished () ;
    void on_sLineEdit_editingFinished () ;

    void on_sLineEdit_focussed(bool focus) ;
    void on_mLineEdit_focussed(bool focus) ;
    void on_hLineEdit_focussed(bool focus) ;

    void on_okButton_clicked () ;
    void on_closeButton_clicked() ;

    void on_fromSetRadio_clicked() ;
    void on_beforeSdRadio_clicked() ;

    void on_comboBox_currentIndexChanged (const QString &textBox) ;

    void on_deleteButton_clicked() ;

    void on_soundBox_stateChanged () ;

    void on_dateButton_clicked();
    void on_clearButton_clicked();
};

#endif // ADDNOTE_H
