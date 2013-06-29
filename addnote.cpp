#include "addnote.h"
#include "ui_addnote.h"

#include <fstream>

using namespace std;


AddNote::AddNote(QWidget *parent, std::map<std::string, Note> *nNote,int sdState) :
    QDialog(parent),
    ui(new Ui::AddNote),
    vNote (nNote)
{
    ui->setupUi(this);

    noteDate.setTime_t(0);



    ui->beforeSdRadio->setEnabled(sdState) ;

    ui->hLineEdit->setText("0");
    ui->mLineEdit->setText("0");
    ui->sLineEdit->setText("0");

    newNote.setMode(AT_TIME) ;

    repopCombo () ;

}

AddNote::~AddNote()
{

    vNote = NULL ;
    delete ui;
}

void AddNote::enableOK()
{
    if (((noteDate.toTime_t() == 0) && (ui->hLineEdit->text().isEmpty()
            || ui->mLineEdit->text().isEmpty()
            || ui->sLineEdit->text().isEmpty()))

            || ui->titleLineEdit->text().isEmpty()
            || (ui->trayCheckBox->isChecked() == false && ui->windowCheckBox->isChecked() == false))
        ui->okButton->setEnabled(false) ;

    else ui->okButton->setEnabled(true) ;
}

void AddNote::on_hLineEdit_editingFinished()
{
    enableOK();
}

void AddNote::on_mLineEdit_editingFinished()
{
    AddNote::enableOK();
}
void AddNote::on_sLineEdit_editingFinished()
{
    AddNote::enableOK();
}


void AddNote::on_titleLineEdit_editingFinished()
{
    if (ui->titleLineEdit->text() == "New" || nameInNotes(ui->titleLineEdit->text()))
    {
        QMessageBox::warning(this, tr("Warning"),
                            tr("Please select other title"),
                            QMessageBox::Ok) ;
        ui->titleLineEdit->clear();
    }
    else
    {
        newNote.setTitle(ui->titleLineEdit->text()) ;
        enableOK() ;
    }
}
void AddNote::on_detailsTextEdit_textChanged()
{
    newNote.setDetails(ui->detailsTextEdit->toPlainText());
}

void AddNote::on_closeButton_clicked()
{
    close() ;
}

void AddNote::on_okButton_clicked()
{
    if(noteDate.toTime_t() == 0)
    {
        newNote.setTime((ui->hLineEdit->text().toInt()) * 3600,
                        ui->mLineEdit->text().toInt() * 60,
                        ui->sLineEdit->text().toInt()) ;

    }

    else
    {
        newNote.setTime(noteDate);
    }

    if (ui->comboBox->currentText() == "New")
        vNote->insert( make_pair(newNote.getTitle().toStdString(), newNote) ) ;
    else
    {
        vNote->find(ui->comboBox->currentText().toStdString())->second = newNote ;
    }

    close () ;
}

void AddNote::on_beforeSdRadio_clicked()
{
    ui->fromSetRadio->setChecked(false) ;
    ui->beforeSdRadio->setChecked(true) ;

    newNote.setMode(BEFORE_SHUT);
}

void AddNote::on_fromSetRadio_clicked()
{
    ui->fromSetRadio->setChecked(true) ;
    ui->beforeSdRadio->setChecked(false) ;

    newNote.setMode(AT_TIME);
}

void AddNote::on_comboBox_currentIndexChanged(const QString &textBox)
{
    if(textBox == "New")
    {
        ui->titleLineEdit->setReadOnly (false) ;
        ui->titleLineEdit->clear();
        ui->detailsTextEdit->clear();
        ui->hLineEdit->clear();
        ui->mLineEdit->clear();
        ui->sLineEdit->clear();
        ui->deleteButton->setEnabled(false) ;
        ui->okButton->setText(tr("Add")) ;
    }

    else
    {

        newNote = vNote->find(ui->comboBox->currentText().toStdString())->second ;


        char hStr[21];
        long long hqint = QDateTime::currentDateTime().secsTo(newNote.getTime()) / 3600;
        sprintf(hStr, "%lld", hqint);

        char mStr[21];
        long long mqint = (QDateTime::currentDateTime().secsTo(newNote.getTime()) / 60) % 60 ;
        sprintf(mStr, "%lld", mqint);

        char sStr[21];
        long long sqint = QDateTime::currentDateTime().secsTo(newNote.getTime()) % 60 ;
        sprintf(sStr,"%lld", sqint);

        ui->titleLineEdit->setText(newNote.getTitle()) ;
        ui->detailsTextEdit->setText(newNote.getDetails()) ;
        ui->hLineEdit->setText(QString::fromUtf8(hStr)) ;
        ui->mLineEdit->setText(QString::fromUtf8(mStr)) ;
        ui->sLineEdit->setText(QString::fromUtf8(sStr)) ;
        ui->beforeSdRadio->setChecked(newNote.getMode() == BEFORE_SHUT) ;
        ui->fromSetRadio->setChecked(newNote.getMode() == AT_TIME) ;
        ui->windowCheckBox->setChecked(newNote.getWindowDisplay());
        ui->trayCheckBox->setChecked(newNote.getTrayDisplay());
        ui->soundBox->setChecked(newNote.isSound()) ;



        ui->deleteButton->setEnabled(true) ;
        ui->okButton->setText(tr("Edit")) ;
        ui->titleLineEdit->setReadOnly(true) ;
    }
}

void AddNote::on_deleteButton_clicked()
{
    if (vNote->find(ui->comboBox->currentText().toStdString()) != vNote->end())
        vNote->erase(vNote->find(ui->comboBox->currentText().toStdString())) ;

    repopCombo () ;
}

void AddNote::repopCombo()
{
    disconnect (ui->comboBox, SIGNAL (currentIndexChanged(const QString)), 0, 0) ;

    ui->comboBox->clear() ;

    connect (ui->comboBox, SIGNAL (currentIndexChanged(const QString)), this, SLOT (on_comboBox_currentIndexChanged (const QString))) ;

    ui->comboBox->addItem(tr("New")) ;

    for( std::map<std::string, Note>::iterator iter = vNote->begin() ; iter!=vNote->end(); iter++)
    {
        ui->comboBox->addItem(iter->second.getTitle()) ;
    }
}


std::string AddNote::IntToString(int IntValue)
{
    char *MyBuff ;
    std::string strRetVal ;

    MyBuff = new char[100] ;

    memset (MyBuff, '\0', 100) ;
    _snprintf(MyBuff, sizeof(MyBuff), "%d", IntValue);
    //itoa (IntValue, MyBuff, 10) ;

    strRetVal = MyBuff ;

    delete [] MyBuff ;

    return (strRetVal) ;
}

int AddNote::GetIntVal(std::string StrConvert)
{
    int intReturn ;

    intReturn = atoi (StrConvert.c_str()) ;

    return (intReturn) ;
}

void AddNote::on_sLineEdit_focussed(bool focus)
{
    if (focus)
        ui->sLineEdit->clear();
    else
        if (ui->sLineEdit->text().isEmpty())
        {
            ui->sLineEdit->setText(QString::fromUtf8("0")) ;
        }
}

void AddNote::on_mLineEdit_focussed(bool focus)
{
    if(focus)
        ui->mLineEdit->clear() ;
    else
        if (ui->mLineEdit->text().isEmpty())
        {
            ui->mLineEdit->setText(QString::fromUtf8("0")) ;
        }
}

void AddNote::on_hLineEdit_focussed(bool focus)
{
    if(focus)
        ui->hLineEdit->clear() ;
    else
        if (ui->hLineEdit->text().isEmpty())
        {
            ui->hLineEdit->setText(QString::fromUtf8("0")) ;
        }
}

void AddNote::on_trayCheckBox_stateChanged()
{
    if (ui->trayCheckBox->isChecked()) newNote.setTrayDisplay(true) ;
    else newNote.setTrayDisplay(false) ;

    enableOK();
}

void AddNote::on_windowCheckBox_stateChanged()
{
    if (ui->windowCheckBox->isChecked()) newNote.setWindowDisplay(true) ;
    else newNote.setWindowDisplay(false) ;

    enableOK();
}

bool AddNote::nameInNotes(QString qstrText)
{
    for (std::map<std::string, Note>::iterator iter = vNote->begin(); iter != vNote->end(); iter++)
    {
        if (iter->second.getTitle() == qstrText) return true ;
    }

    return false ;
}

void AddNote::on_dateButton_clicked()
{
    DateAndTime* date = new DateAndTime(this, &noteDate);
    date->show();

    if(noteDate.toTime_t() != 0)
    {
        ui->hLineEdit->setReadOnly(true);
        ui->mLineEdit->setReadOnly(true);
        ui->sLineEdit->setReadOnly(true);

        ui->beforeSdRadio->setDisabled(true);
        on_fromSetRadio_clicked();

    }

    else
    {
        ui->hLineEdit->setReadOnly(false);
        ui->mLineEdit->setReadOnly(false);
        ui->sLineEdit->setReadOnly(false);

    }
}

void AddNote::on_clearButton_clicked()
{
    noteDate.setTime_t(0);
    ui->beforeSdRadio->setDisabled(false);
}

void AddNote::on_soundBox_stateChanged()
{
    if (ui->soundBox->isChecked())
	{
        newNote.setSound(true);
	}
    else 
	{
		newNote.setSound(false);
	}

}
