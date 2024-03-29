# Programação Orientada a Objetos

Este repositório é destinado para a documentação do projeto da disciplina de Programação Orientada a Objetos (PRG22107).

O objetivo do projeto é criar uma interface voltada para o controle e configurações de um sistema de irrigação de jardim.

Lista de Materiais:

| Dispositivos |  Quantidade |
| ------------ | ----------- |
| Higrômetro - YL 69 |   1   |
|  Relé simulando uma Mini-bomba |   1   |
| Arduino MEGA 2560 R3 |  1  |
| Cabo/Fonte Arduino |      1     |

Funções:

- Irrigar a planta através de um controle voltado a umidade do solo.
- Controle de acionamento da mini-bomba de água.
- Configuração de limiar de umidade.

Os dados dos sensores e atuadores serão manipulados pelo controlador e pela interface, comunicando-se via serial.

Diagrama de classes do projeto:

![Diagrama de Classes](https://github.com/maiteluisaa/prog22107/blob/main/figuras/fluxo.png)

A interface final contém 2 modos de operação, automático e manual. Automático: aciona a mini-bomba conforme o sensor de humidade. Manual: aciona a mini-bomba conforme o sinal enviado pelo usuário final.

![Interface Final](https://github.com/maiteluisaa/prog22107/blob/main/figuras/UI.png)
