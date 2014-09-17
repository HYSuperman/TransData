#ifndef HARDCONFIGURE_H
#define HARDCONFIGURE_H

#include <QDialog>
#include "ui_hardconfigure.h"

class QProcess;

class hardConfigure : public QDialog, public Ui::hardConfigure
{
    Q_OBJECT
public:
    explicit hardConfigure(QWidget *parent = 0);
    QProcess *mac_phy_Process;
    QProcess *make_device;
    QProcess *reset_test;


private:
    QString filename;
	int state;
    //mac layer
    QString sourceAddh;
    QString sourceAddl;
    QString destAddh;
    QString destAddl;
    int cca_threshold;
    int difsT;
    int sifsT;
    int ack_timeout;
    //phy Layer
	int rate;
    int psduLength;
    //uhd set
    QString rx_center_frequency;
    QString tx_center_frequency;
    QString rx_sample_rate;
    QString tx_sample_rate;
    int rx_gain;
    int tx_gain;


    void setReg();
    void getIntValue();
    void output(QTextStream &Out);
    void getStateRate();
    void getString();
    void toLowerUnit(QString & string, int mode);

signals:

public slots:

private slots:
    void run_make_device();
    void run_reset_test();
    void getFile();
    void run_mac_phy();
	void Save();
    void on_lineEdit_5_textChanged();
    void on_lineEdit_12_textChanged();
    void on_lineEdit_1_textChanged();
    void on_lineEdit_2_textChanged();
    void on_lineEdit_7_textChanged();
    void on_lineEdit_9_textChanged();
    void on_lineEdit_8_textChanged();
    void on_lineEdit_11_textChanged();
    void on_lineEdit_10_textChanged();
    void on_buttonBox_clicked(QAbstractButton *button);

    void writeSettings();
    void readSettings();

};

#endif // HARDCONFIGURE_H
