#include "hardconfigure.h"
#include "outputdialog.h"
#include <QProcess>
#include <QFile>
#include <QtGui>
#include <iostream>

#define APPLYABLE lineEdit_5->hasAcceptableInput()&&lineEdit_12->hasAcceptableInput()&&\
                  lineEdit_1->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&\
                  lineEdit_7->hasAcceptableInput()&&lineEdit_9->hasAcceptableInput()&&\
                  lineEdit_8->hasAcceptableInput()&&lineEdit_11->hasAcceptableInput()&&\
                  lineEdit_10->hasAcceptableInput()



hardConfigure::hardConfigure(QWidget *parent) :
    QDialog(parent)
{
   setupUi(this);

   mac_phy_Process = new QProcess(this);
   make_device = new QProcess(this);
   reset_test = new QProcess(this);

   buttonBox->button(QDialogButtonBox::Ok)->setText(tr("&Run"));
   buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);//disable apply button
   setReg();
   buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);//check if it is appliable now
   connect(pushButton, SIGNAL(clicked()), this, SLOT(getFile()));
   connect(pushButton_2, SIGNAL(clicked()), this , SLOT(run_make_device()));
   connect(pushButton_3, SIGNAL(clicked()), this, SLOT(run_reset_test()));

}

void hardConfigure::getFile(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(dialog.exec()){
    fileNames = dialog.selectedFiles();
    filename = fileNames.at(0).toLocal8Bit().constData();
    lineEdit->setText(filename);
    }

}

void hardConfigure::Save(){
    QFile file("configure_file.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        std::cout << "Cannot open file for writing: "
             << qPrintable(file.errorString()) << std::endl;
		return;
	}

    getIntValue();
    getStateRate();
    getString();
    QTextStream out(&file);
    output(out);
}

void hardConfigure::setReg(){

    QRegExp regExp1("^[0-9]*[1-9][0-9]*$");//positive int regression
    lineEdit_5->setValidator(new QRegExpValidator(regExp1, this));//set a validator for cca threshold line edit
    lineEdit_12->setValidator(new QRegExpValidator(regExp1, this));
    lineEdit_1->setValidator(new QRegExpValidator(regExp1, this));
    lineEdit_2->setValidator(new QRegExpValidator(regExp1, this));
    lineEdit_7->setValidator(new QRegExpValidator(regExp1, this));

}

void hardConfigure::on_lineEdit_5_textChanged(){
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_12_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_1_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_2_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_7_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_9_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_8_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_11_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_10_textChanged(){
buttonBox->button(QDialogButtonBox::Apply)->setEnabled(APPLYABLE);
}

void hardConfigure::output(QTextStream &Out){

    Out << "file_name = " << filename << endl;
    Out << "state = " << state << endl;
    Out << "source_addr_h = 0x" << sourceAddh << endl;
    Out << "source_addr_l = 0x" << sourceAddl << endl;
    Out << "dest_addr_h = 0x" << destAddh << endl;
    Out << "dest_addr_l = 0x" << destAddl << endl;
    Out << "cca_threshold = " << cca_threshold << endl;
    Out << "pdu_len = " << psduLength << endl;
    Out << "rate_choosed = " << rate << endl;
    Out << "ack_timeout = " << ack_timeout << endl;
    Out << "difs = " << difsT << endl;
    Out << "sifs = " << sifsT << endl;
    Out << "rx_center_freqency = " << rx_center_frequency << ".0" << endl;
    Out << "tx_center_freqency = " << tx_center_frequency << ".0" << endl;
    Out << "rx_sample_rate = " << rx_sample_rate << endl;
    Out << "tx_sample_rate = " << tx_sample_rate << endl;
    Out << "rx_gain = " << rx_gain << endl;
    Out << "tx_gain = " << tx_gain << endl;

//    QDateTime current_date_time = QDateTime::currentDateTime();
//    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:ddd");

}


void hardConfigure::getIntValue(){

    /* lineedit */
    cca_threshold = lineEdit_5->text().toInt();
    difsT = lineEdit_12->text().toInt();
    sifsT = lineEdit_1->text().toInt();
    ack_timeout = lineEdit_2->text().toInt();
    psduLength = lineEdit_7->text().toInt();


    /* spinbox 1-2 */
    rx_gain = spinBox_1->text().toInt();
    tx_gain = spinBox_2->text().toInt();
}

void hardConfigure::getStateRate(){
    if(radioButton->isChecked())
        state = 0;
    else if (radioButton_9->isChecked())
        state = 1;

    if(radioButton_1->isChecked())
        rate = 1;
    else if(radioButton_2->isChecked())
        rate = 2;
    else if(radioButton_3->isChecked())
        rate = 4;
    else if(radioButton_5->isChecked())
        rate = 5;
    else if(radioButton_6->isChecked())
        rate = 6;
    else if(radioButton_7->isChecked())
        rate = 7;
    else if(radioButton_8->isChecked())
        rate = 8;
}

void hardConfigure::getString(){

    filename = lineEdit->text();
    QString source = lineEdit_3->text();
    QStringList source1 = source.split(":");
    sourceAddh = source1.join("").left(6);
    sourceAddl = source1.join("").right(6);

    QString dest = lineEdit_4->text();
    QStringList dest1 = dest.split(":");
    destAddh = dest1.join("").left(6);
    destAddl = dest1.join("").right(6);

    rx_center_frequency = lineEdit_9->text();
    tx_center_frequency = lineEdit_8->text();
    rx_sample_rate = lineEdit_11->text();
    tx_sample_rate = lineEdit_10->text();

    if(comboBox_1->currentIndex() == 1)
        toLowerUnit(tx_center_frequency, 0);
    if(comboBox_2->currentIndex() == 1)
        toLowerUnit(rx_center_frequency, 0);
    if(comboBox_3->currentIndex() == 1)
        toLowerUnit(tx_sample_rate, 1);
    if(comboBox_4->currentIndex() == 1)
        toLowerUnit(rx_sample_rate, 1);


}

void hardConfigure::toLowerUnit(QString & string, int mode){

    QChar dot = '.';
    QString lackingZero;//for a non-float number to append zeros only
    int index = string.indexOf(dot);//index of the origin zero
    int newLocale;//the new location of '.'
    int lackZero;//for a float number to append the certain number of zero
    int zeroBias = 9;//how should we convert

    int length = string.size();

    if(mode == 0){//GHZ mode
        lackingZero = "000000000";
    }
    else if(mode == 1){//MSPS mode
        zeroBias = 6;
        lackingZero = "000000";
    }

    if(index == -1)//if there is no '.'
        string.append(lackingZero);
    else if(length - index - 1 > zeroBias){//if the fraction part is too long
        newLocale = index + zeroBias;
        string.remove(index, 1);
        if(string.at(0) == '0'){//if the form is 0.***, remove the '0'
            string.remove(0, 1);
            newLocale--;
        }
        string.insert(newLocale, dot);
        }
    else{//if the fraction part is just appropriate
        lackZero = zeroBias - (length - index - 1);
        string.remove(index, 1);
        if(string.at(0) == '0')//if the form is 0.***, remove the '0'
            string.remove(0, 1);
        while(lackZero--)
            string.append("0");
    }
}

void hardConfigure::on_buttonBox_clicked(QAbstractButton *button)
{
    if(buttonBox->buttonRole(button)== buttonBox->ApplyRole)
        Save();
    if(buttonBox->buttonRole(button)== buttonBox->AcceptRole)
		run_mac_phy();
}

void hardConfigure::run_make_device(){
    make_device->start("../sPciDriver/make_device");
    if(!make_device->waitForStarted())
        std::cout << "Failed to start make_device" << std::endl;
    std::cout << "make_device started" << std::endl;
    if(make_device->waitForFinished())
        std::cout << "make_device finished" << std::endl;
}



void hardConfigure::run_reset_test(){
    QStringList para;
    para << lineEdit_6->text();
    make_device->start("./reset_test", para);
    if(!make_device->waitForStarted())
        std::cout << "Failed to start reset_test" << std::endl;
    std::cout << "reset_test started" << std::endl;
    if(make_device->waitForFinished())
        std::cout << "finished reset_test" << std::endl;

}

void hardConfigure::run_mac_phy(){
     //QProcess::execute("./constellation_mapping");
    mac_phy_Process->start("./low_mac configure_file.txt");
    //mac_phy_Process->start("./a.out");
    //mac_phy_Process->start("./constellation_mapping");
    //std::cout << "1111" << std::endl;
    if (!mac_phy_Process->waitForStarted())
        std::cout << "Failed to start" << std::endl;
    std::cout << "low_mac started..." << std::endl;
    this->hide();
    outPutDialog *outPut = new outPutDialog(this);
    outPut->show();
}



