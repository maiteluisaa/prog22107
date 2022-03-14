#ifndef CASAAUTOMATIZADA_H
#define CASAAUTOMATIZADA_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class CasaAutomatizada; }
QT_END_NAMESPACE

class SensorInt{

public:

    SensorInt();
    ~SensorInt();

    int getDado (){
        return dado;
    }

    void setDado (int setdado){
        dado = setdado;
    }

private:
double dado;
};

class SensorDouble{

public:

    SensorDouble();
    ~SensorDouble();

    double getDado (){
        return dado;
    }

    void setDado (double setdado){
        dado = setdado;
    }

private:
double dado;
};

class Atuador{
public:

    Atuador();
    ~Atuador();

    bool atuar (bool ato){
        return ato;
    };
};

class ControladorInt : SensorInt, Atuador {

public:
    ControladorInt();
    ~ControladorInt();
    void setVariavelControle(int variavel){
        variavelControle = variavel;
    }
    int getVariavelControle(){

        return variavelControle;
    }

    int getDadoSensor(){
        return dadoSensor;
    }

    void setDadoSensor(int dado){
        setDado(dado);
        dadoSensor = getDado();
    }

    bool estadoAtual (){
        return atuador;
    }

private:
    int id;
    int variavelControle;
    int dadoSensor;
    bool atuador;
};


class CasaAutomatizada : public QDialog
{
    Q_OBJECT

public:
    CasaAutomatizada(QWidget *parent = nullptr);
    ~CasaAutomatizada();

private slots:
    void on_ligaVentilador_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_SpinBox_valueChanged(int arg1);

    void on_umidade_valueChanged(int arg1);

    void on_pushButton_9_clicked();

    void on_abrePortao_clicked();

    void on_fechaPortao_clicked();

    void on_regaJardim_clicked();

    void on_naoregaJardim_clicked();

    void on_horizontalSliderGas_valueChanged(int value);

    void on_ligaExaustor_clicked();

    void on_naoligaExaustor_clicked();

private:
    Ui::CasaAutomatizada *ui;
    Atuador *portao;
    Atuador *ventilador;
    Atuador *minibomba;
    ControladorInt *temperatura;
    ControladorInt *umidade;
    ControladorInt *gas;
};
#endif // CASAAUTOMATIZADA_H
