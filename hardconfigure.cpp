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
   readSettings();

   pushButton_2->hide();

   mac_phy_Process = new QProcess(this);
   make_device = new QProcess(this);
   reset_test = new QProcess(this);
   buttonBox->button(QDialogButtonBox::Ok)->setText(tr("&Run"));
   setReg();
   buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);//check if it is appliable now
   connect(pushButton, SIGNAL(clicked()), this, SLOT(getFile()));
   connect(pushButton_2, SIGNAL(clicked()), this, SLOT(run_make_device()));
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
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_12_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_1_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_2_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_7_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_9_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_8_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_11_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
}

void hardConfigure::on_lineEdit_10_textChanged(){
buttonBox->button(QDialogButtonBox::Ok)->setEnabled(APPLYABLE);
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
    if(buttonBox->buttonRole(button)== buttonBox->AcceptRole){
        writeSettings();
        run_reset_test();
        Save();
		run_mac_phy();
    }
}


void hardConfigure::run_make_device(){
    make_device->start("../sPciDriver/make_device");
    if(!make_device->waitForStarted())
        std::cout << "Failed to start make_device" << std::endl;
    std::cout << "make_device started" << std::endl;
    if(make_device->waitForFinished())
        std::cout << "Finished make_device" << std::endl;
    else
        std::cout << "Failed make_device" << std::endl;
}




void hardConfigure::run_reset_test(){
    QString para = "1";
    reset_test->start("./reset_test", QStringList() << para);
    if(!reset_test->waitForStarted())
        std::cout << "Failed to start reset_test" << std::endl;
    std::cout << "Reset_test started" << std::endl;
    if(reset_test->waitForFinished())
        std::cout << "Finished reset_test" << std::endl;
    else
        std::cout << "Failed reset_test" << std::endl;

}

void hardConfigure::run_mac_phy(){
    mac_phy_Process->start("./low_mac configure_file.txt");
    if (!mac_phy_Process->waitForStarted())
        std::cout << "Failed to start low_mac" << std::endl;
    std::cout << "Low_mac started..." << std::endl;
    this->hide();
    outPutDialog *outPut = new outPutDialog(this);
    outPut->show();
}


void hardConfigure::writeSettings(){
    QSettings settings("Peking University", "GRT");
    settings.setValue("fileChoosed", lineEdit->text());
    settings.setValue("state",  buttonGroup->checkedId());
    settings.setValue("sourcemacaddress", lineEdit_3->text());
    settings.setValue("destmacaddress", lineEdit_4->text());
    settings.setValue("ccathreshold", lineEdit_5->text());
    settings.setValue("difs", lineEdit_12->text());
    settings.setValue("sifs", lineEdit_1->text());
    settings.setValue("acktimeout", lineEdit_2->text());
    settings.setValue("rate", buttonGroup_2->checkedId());
    settings.setValue("psdulength", lineEdit_7->text());
    settings.setValue("rxcenterfre", lineEdit_9->text());
    settings.setValue("rxcenterfrecombo", comboBox_2->currentIndex());
    settings.setValue("rxsamplerate", lineEdit_11->text());
    settings.setValue("rxsampleratecombo", comboBox_4->currentIndex());
    settings.setValue("rxgain", spinBox_1->value());
    settings.setValue("txcenterfre", lineEdit_8->text());
    settings.setValue("txcenterfrecombo", comboBox_1->currentIndex());
    settings.setValue("txsamplerate", lineEdit_10->text());
    settings.setValue("txsampleratecombo", comboBox_3->currentIndex());
    settings.setValue("txgain", spinBox_2->value());


}


void hardConfigure::readSettings(){
    QSettings settings("Peking University", "GRT");
    lineEdit->setText(settings.value("fileChoosed", "grt.jpg").toString());
    buttonGroup->button(settings.value("state", -3).toInt())->setChecked(true);
    lineEdit_3->setText(settings.value("sourcemacaddress", "ce:ca:22:ce:ca:22").toString());
    lineEdit_4->setText(settings.value("destmacaddress", "ce:ca:11:ce:ca:11").toString());
    lineEdit_5->setText(settings.value("ccathreshold", "65535").toString());
    lineEdit_12->setText(settings.value("difs", "34").toString());
    lineEdit_1->setText(settings.value("sifs", "16").toString());
    lineEdit_2->setText(settings.value("acktimeout", "1250").toString());
    buttonGroup_2->button(settings.value("rate", -9).toInt())->setChecked(true);
    lineEdit_7->setText(settings.value("psdulength", "4095").toString());
    lineEdit_9->setText(settings.value("rxcenterfre", "2.457").toString());
    comboBox_2->setCurrentIndex(settings.value("rxcenterfrecombo", 0).toInt());
    lineEdit_11->setText(settings.value("rxsamplerate", "12.5").toString());
    comboBox_4->setCurrentIndex(settings.value("rxsampleratecombo", 0).toInt());
    spinBox_1->setValue(settings.value("rxgain", 20).toInt());
    lineEdit_8->setText(settings.value("txcenterfre", "2.457").toString());
    comboBox_1->setCurrentIndex(settings.value("txcenterfrecombo", 0).toInt());
    lineEdit_10->setText(settings.value("txsamplerate", "12.5").toString());
    comboBox_3->setCurrentIndex(settings.value("txsampleratecombo", 0).toInt());
    spinBox_2->setValue(settings.value("txgain", 20).toInt());

}



