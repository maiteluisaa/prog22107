#define MINIPUMP 52
#define HIGRO A0

unsigned long tarefanterior1 = millis();
unsigned long tarefanterior2 = millis();

int analogSoloSeco = 1300; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 900; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

int valorLidoHigro; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
int valorLidoRes;

int acionamentoMiniBomba = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(MINIPUMP, OUTPUT);    // configura o pino digital 13 como saída
  pinMode(HIGRO, INPUT);
  Serial.begin(9600); //INICIALIZA A SERIAL 
  digitalWrite(MINIPUMP,HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - tarefanterior1) > 250){
    Sensor();
    tarefanterior1 = millis(); 
  }
  
  if ((millis() - tarefanterior2) > 250){
    Atuador();
    tarefanterior2 = millis(); 
  }
} 

void Sensor() {
  valorLidoHigro = constrain(analogRead(HIGRO), analogSoloMolhado, analogSoloSeco); //MANTÉM valor Lido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  //valorLidoHigro = constrain(500, analogSoloMolhado, analogSoloSeco); //MANTÉM valor Lido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLidoHigro = map(valorLidoHigro, analogSoloMolhado, analogSoloSeco, percSoloMolhado, percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  Serial.print(valorLidoHigro);
}

void Atuador() {
  if (Serial.available() > 0){
    acionamentoMiniBomba = Serial.readString().toInt();
    if(acionamentoMiniBomba == 1){
    digitalWrite(MINIPUMP, LOW);
    }
    if(acionamentoMiniBomba == 0){
    digitalWrite(MINIPUMP, HIGH); 
  }
 }
}
