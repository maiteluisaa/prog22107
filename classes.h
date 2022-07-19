#ifndef CLASSES_H
#define CLASSES_H

class Atuador
{
private:
    int _estado;
public:
    Atuador() {_estado = 0;};
    void SetEstado(int estado) {_estado = estado;};
    int GetEstado() {return _estado;};
};

class Controlador
{
private:
    int _limiar;

public:
    Controlador() {_limiar = 0;};
    void SetLimiar(int limiar) { _limiar = limiar;};
    int GetLimiar(){return _limiar;};
};

class Sensor
{
private:
    int _dado;
public:
    Sensor() {_dado = 0;};
    int GetDado() {return _dado;};
    void SetDado(int dado) {_dado = dado;};
};

#endif // CLASSES_H
