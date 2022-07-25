#include "widget.h"
#include "ui_widget.h"
#include "classes.h"
#include <iostream>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->spinBox->setDisplayIntegerBase(10);

    ui->comboBox_2->setCurrentText("Manual");
    ui->spinBox->setVisible(0);
    ui->pushButton_2->setVisible(1);
    ui->label_4->setVisible(1);
    ui->label_5->setVisible(0);
    ui->horizontalSlider->setVisible(0);

    this->serialPort = new QSerialPort;

    this->atuador = new class Atuador();
    this->controlador = new class Controlador();
    this->sensor = new class Sensor();

    this->time = QTime::currentTime();
    this->date = QDate::currentDate();

    this->atuador->SetEstado(0);
    this->controlador->SetLimiar(0);
    this->sensor->SetDado(0);

    //Montagem da lista de portas e alimentação do combobox com a lista de portas disponíveis
    QStringList ports;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    int i = 0;
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos){
        ports.insert(i,serialPortInfo.portName());
        i++;
    }

    ui->comboBox_port->insertItems(0,ports);

    //Criação da lista de velocidades da comunicação serial e alimentação do combobox baudrate
    QStringList bauds;
    bauds << "9600" << "19200" << "38400" << "57600" << "115200";
    ui->comboBox_baud->insertItems(0,bauds);

    connect(ui->pushButton_connect,SIGNAL(clicked(bool)),this,SLOT(connectToSerial()));

    connect(this->serialPort,SIGNAL(readyRead()),this,SLOT(startReading()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connectToSerial()
{
    /*Na conexão fazemos a abertura ou fechamento da porta.*/
    if (this->serialPort->isOpen()){
        this->serialPort->close();
        ui->label_status->setText("Desconectado");
        ui->pushButton_connect->setText("Conectar");
        return;
    }
    //se for para abrir, pegamos os parâmetros de velocidade e porta a abrir.
    this->serialPort->setPortName(ui->comboBox_port->currentText());
    this->serialPort->setBaudRate(ui->comboBox_baud->currentText().toUInt());

    if (!this->serialPort->open(QIODevice::ReadWrite)){
        ui->label_status->setText("Falha ao tentar conectar");
        return;
    }
    ui->label_status->setText("Conectado");
    ui->pushButton_connect->setText("Desconectar");

    emit ReadyRead(true);
}

void Widget::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if (arg1=="Manual"){
        ui->spinBox->setVisible(0);
        ui->pushButton_2->setVisible(1);
        ui->label_4->setVisible(1);
        ui->label_5->setVisible(0);
        ui->horizontalSlider->setVisible(0);
    }
    if(arg1=="Automático"){
        ui->pushButton_2->setVisible(0);
        ui->spinBox->setVisible(1);
        ui->label_4->setVisible(0);
        ui->label_5->setVisible(1);
        ui->horizontalSlider->setVisible(1);
    }
}


void Widget::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
    this->controlador->SetLimiar(arg1);
}

void Widget::startReading(){

    this->time=QTime::currentTime();

    QByteArray readData = this->serialPort->readAll();
    QString dadoREC = readData;

    bool bStatus = false;
    uint nHex = dadoREC.toUInt(&bStatus,10);

    this->sensor->SetDado(nHex);

    //qDebug() << dadoREC.toUtf8().toUInt(&bStatus,16);
    qDebug() << nHex;
    qDebug() << dadoREC.toLatin1();
    qDebug() << sizeof(dadoREC);

    write();
    report();
}


void Widget::write(){

    qDebug() << "Atuador";
    qDebug() << atuador->GetEstado();
    qDebug() << "Limiar";
    qDebug() << controlador->GetLimiar();
    qDebug() << "Sensor";
    qDebug() << sensor->GetDado();

    if(ui->comboBox_2->currentText() == "Automático"){

        if(this->sensor->GetDado() <= this->controlador->GetLimiar()){
            this->atuador->SetEstado(1);

        }
        else {
             this->atuador->SetEstado(0);
        }
    }

    QString dado = QString::number(this->atuador->GetEstado());
    QByteArray dadoserial = dado.toLatin1();
    this->serialPort->write(dadoserial, sizeof(dadoserial));
}

void Widget::on_pushButton_2_clicked()
{
    if(this->atuador->GetEstado() == 0){
        this->atuador->SetEstado(1);
        ui->pushButton_2->setText("Desativar");
    }
    else if(this->atuador->GetEstado() == 1){
        this->atuador->SetEstado(0);
        ui->pushButton_2->setText("Ativar");
    }
}


void Widget::on_pushButton_3_clicked()
{
    QString _pastatual = "C:/Users/ma057095/Jardim/Log/" + QString::number(date.year()) + "_" + QString::number(date.month()) + "_" + QString::number(date.day());
    QString _arquivo = "/log.txt";

    QString link=_pastatual + _arquivo;
    QDesktopServices::openUrl(QUrl(link));
}

void Widget::report(){

    QString _pastatual = "C:/Users/ma057095/Jardim/Log/" + QString::number(date.year()) + "_" + QString::number(date.month()) + "_" + QString::number(date.day());
    QString _arquivo = "/log.txt";
    QString _arquivoatual = _pastatual + _arquivo;

    QDir dirt(_pastatual);
        if (!dirt.exists()){
            qDebug() << "Criando pasta";
            dirt.mkpath(_pastatual);
    }

    QFile arquivoatual(_arquivoatual);
    if(!arquivoatual.open(QFile::ReadWrite|QFile::Text)){
        QMessageBox::warning(this,"ERRO", "Erro ao abrir o arquivo.");
    }

    QTextStream saidarec(&arquivoatual);

    QString line = saidarec.readLine();
    while (!saidarec.atEnd()){
        line = saidarec.readLine();
    }

    QString sensor = QString::number(this->sensor->GetDado());
    QString controlador = QString::number(this->controlador->GetLimiar());
    QString atuador = QString::number(this->atuador->GetEstado());

    saidarec << "\n  Modo         Humidade   Limiar   Atuador   Horário\n";
    saidarec << "  " + ui->comboBox_2->currentText() + "          " + sensor + "         " + controlador + "         " + atuador + "      " + time.toString();

    arquivoatual.flush();
    arquivoatual.close();
}


void Widget::on_spinBox_textChanged(const QString &arg1)
{
    this->controlador->SetLimiar(arg1.toInt());
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    this->controlador->SetLimiar(value);
    ui->spinBox->setValue(value);
}

