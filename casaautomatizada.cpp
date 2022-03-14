#include "casaautomatizada.h"
#include "./ui_casaautomatizada.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

CasaAutomatizada::CasaAutomatizada(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CasaAutomatizada)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentText("Manual");
    ui->ligaVentilador->setEnabled(true);
    ui->desligaVentilador->setEnabled(true);
    ui->abrePortao->setEnabled(true);
    ui->fechaPortao->setEnabled(true);
    ui->regaJardim->setEnabled(true);
    ui->naoregaJardim->setEnabled(true);
    ui->ligaExaustor->setEnabled(true);
    ui->naoligaExaustor->setEnabled(true);
    ui->SpinBox->setEnabled(false);
    ui->umidade->setEnabled(false);
    ui->horizontalSliderGas->setEnabled(false);

}

CasaAutomatizada::~CasaAutomatizada()
{
    delete ui;
}


void CasaAutomatizada::on_ligaVentilador_clicked()
{
    ventilador->atuar(1);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentText() == "Manual")
    {
        ui->ligaVentilador->setEnabled(true);
        ui->desligaVentilador->setEnabled(true);
        ui->abrePortao->setEnabled(true);
        ui->fechaPortao->setEnabled(true);
        ui->regaJardim->setEnabled(true);
        ui->naoregaJardim->setEnabled(true);
        ui->ligaExaustor->setEnabled(true);
        ui->naoligaExaustor->setEnabled(true);
        ui->SpinBox->setEnabled(false);
        ui->umidade->setEnabled(false);
        ui->horizontalSliderGas->setEnabled(false);
    }

    if(ui->comboBox->currentText() == "Automático")
    {
        ui->ligaVentilador->setEnabled(false);
        ui->desligaVentilador->setEnabled(false);
        ui->abrePortao->setEnabled(false);
        ui->fechaPortao->setEnabled(false);
        ui->regaJardim->setEnabled(false);
        ui->naoregaJardim->setEnabled(false);
        ui->ligaExaustor->setEnabled(false);
        ui->naoligaExaustor->setEnabled(false);
        ui->SpinBox->setEnabled(true);
        ui->umidade->setEnabled(true);
        ui->horizontalSliderGas->setEnabled(true);
    }

}


void CasaAutomatizada::on_SpinBox_valueChanged(int arg1)
{
    temperatura->setVariavelControle(ui->SpinBox->value());

    if(temperatura->getVariavelControle() < temperatura->getDadoSensor()){
        ventilador->atuar(1);
        //abrir serial e mandar comando
    }

    if(temperatura->getVariavelControle() >= temperatura->getDadoSensor()){
        ventilador->atuar(0);
        //abrir serial e mandar comando
    }
}

void CasaAutomatizada::on_umidade_valueChanged(int arg1)
{
    umidade->setVariavelControle(ui->umidade->value());

    if(umidade->getVariavelControle() <= umidade->getDadoSensor()){
        minibomba->atuar(0);
        //abrir serial e mandar comando
    }

    if(gas->getVariavelControle()  > umidade->getDadoSensor()){
        minibomba->atuar(0);
        //abrir serial e mandar comando
    }
}


void CasaAutomatizada::on_pushButton_9_clicked()
{
    QApplication::quit();
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_abrePortao_clicked()
{
    portao->atuar(1);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_fechaPortao_clicked()
{
    portao->atuar(0);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_regaJardim_clicked()
{
    minibomba->atuar(1);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_naoregaJardim_clicked()
{
    minibomba->atuar(0);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_horizontalSliderGas_valueChanged(int value)
{
    gas->setVariavelControle(ui->horizontalSliderGas->value());

    if(gas->getVariavelControle() < gas->getDadoSensor()){
        ventilador->atuar(0);
        //abrir serial e mandar comando
    }

    if(gas->getVariavelControle()  >= gas->getDadoSensor()){
        ventilador->atuar(1);
        //abrir serial e mandar comando
    }
}


void CasaAutomatizada::on_ligaExaustor_clicked()
{
    ventilador->atuar(1);
    //abrir serial e mandar comando
}


void CasaAutomatizada::on_naoligaExaustor_clicked()
{
    ventilador->atuar(0);
    //abrir serial e mandar comando
}

