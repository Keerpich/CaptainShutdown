#include "addnote.h"
#include "ui_addnote.h"

AddNote::AddNote(QWidget *parent, std::map<std::string, Note> *nNote,int sdState) :
    QDialog(parent),
    ui(new Ui::AddNote),
    vNote (nNote)
{
    ui->setupUi(this);

    ui->beforeSdRadio->setEnabled(sdState) ;

    newNote.setH(0);
    newNote.setM(0);
    newNote.setS(0);

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
    if (ui->hLineEdit->text().isEmpty()
            || ui->mLineEdit->text().isEmpty()
            || ui->sLineEdit->text().isEmpty()
            || ui->titleLineEdit->text().isEmpty()
            || (ui->trayCheckBox->isChecked() == false && ui->windowCheckBox->isChecked() == false))
        ui->okButton->setEnabled(false) ;

    else ui->okButton->setEnabled(true) ;
}

void AddNote::on_hLineEdit_editingFinished()
{
    newNote.setH(atoi(ui->hLineEdit->text().toStdString().c_str()));
    enableOK() ;
}

void AddNote::on_mLineEdit_editingFinished()
{
    if (GetIntVal(ui->mLineEdit->text().toStdString()) >= 60)
    {
        newNote.setH(newNote.getH() + GetIntVal(ui->mLineEdit->text().toStdString()) / 60) ;
        ui->hLineEdit->setText(QString::fromUtf8(IntToString(newNote.getH()).c_str())) ;
    }

    newNote.setM(atoi(ui->mLineEdit->text().toStdString().c_str()) % 60) ;
    ui->mLineEdit->setText(QString::fromUtf8(IntToString(newNote.getM()).c_str())) ;

    enableOK () ;
}
void AddNote::on_sLineEdit_editingFinished()
{
    if (GetIntVal(ui->sLineEdit->text().toStdString()) >= 60)
    {
        newNote.setM(newNote.getM() + GetIntVal(ui->sLineEdit->text().toStdString()) / 60) ;
        ui->mLineEdit->setText(QString::fromUtf8(IntToString(newNote.getM()).c_str())) ;

        if (GetIntVal(ui->mLineEdit->text().toStdString()) >= 60)
        {
            newNote.setH(newNote.getH() + GetIntVal(ui->mLineEdit->text().toStdString()) / 60) ;
            ui->hLineEdit->setText(QString::fromUtf8(IntToString(newNote.getH()).c_str())) ;

            newNote.setM(atoi(ui->mLineEdit->text().toStdString().c_str()) % 60) ;
            ui->mLineEdit->setText(QString::fromUtf8(IntToString(newNote.getM()).c_str())) ;
        }
    }

    newNote.setS(atoi(ui->sLineEdit->text().toStdString().c_str()) % 60) ;
    ui->sLineEdit->setText(QString::fromUtf8(IntToString(newNote.getS()).c_str())) ;

    enableOK () ;
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
        ui->hLineEdit->setText(QString::fromUtf8(IntToString(newNote.getH()).c_str())) ;
        ui->mLineEdit->setText(QString::fromUtf8(IntToString(newNote.getM()).c_str())) ;
        ui->sLineEdit->setText(QString::fromUtf8(IntToString(newNote.getS()).c_str())) ;
        ui->deleteButton->setEnabled(false) ;
        ui->okButton->setText(tr("Add")) ;
    }

    else
    {
        newNote = vNote->find(ui->comboBox->currentText().toStdString())->second ;

        ui->titleLineEdit->setText(newNote.getTitle()) ;
        ui->detailsTextEdit->setText(newNote.getDetails()) ;
        ui->hLineEdit->setText(QString::fromUtf8(IntToString(newNote.getH()).c_str())) ;
        ui->mLineEdit->setText(QString::fromUtf8(IntToString(newNote.getM()).c_str())) ;
        ui->sLineEdit->setText(QString::fromUtf8(IntToString(newNote.getS()).c_str())) ;
        ui->beforeSdRadio->setChecked(newNote.getMode() == BEFORE_SHUT) ;
        ui->fromSetRadio->setChecked(newNote.getMode() == AT_TIME) ;

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
    snprintf(MyBuff, sizeof(MyBuff), "%d", IntValue);
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
            newNote.setS(0) ;
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
            newNote.setM(0) ;
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
            newNote.setH(0) ;
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
