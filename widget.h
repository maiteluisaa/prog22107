#ifndef WIDGET_H
#define WIDGET_H

#include "classes.h"
#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QIODevice>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QDate date;
    QTime time;
    QSerialPort *serialPort;
    Atuador *atuador;
    Sensor *sensor;
    Controlador *controlador;
    Widget(QWidget *parent = nullptr);
    void report();
    void write();
    ~Widget();

private slots:
    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void connectToSerial();

    void startReading();

    void on_spinBox_textChanged(const QString &arg1);

    void on_horizontalSlider_valueChanged(int value);

signals:
    void ReadyRead(bool ok);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
