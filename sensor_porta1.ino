//definindo as portas de entrada
#define pinSensorFora 2 
#define pinSensorDentro 3 
#define pinBotaoReiniciar A0

//definindo os modos 
#define ESPERA 0
#define ENTRANDO 1
#define SAINDO 2

//definindo portas do LED rgb
#define vermelho 12
#define azul 10
#define verde 9

//definindo as variáveis
int pessoas = 0;
int limitePessoas = 4;
int modo = ESPERA;
 
void setup() {
  pinMode(pinSensorFora, INPUT);
  pinMode(pinSensorDentro, INPUT);
  pinMode(pinBotaoReiniciar, INPUT_PULLUP);
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  
  Serial.begin(9600); 
}

void loop() {
  //leitura dos sensores
  bool estadoSensorFora = !digitalRead(pinSensorFora);
  bool estadoSensorDentro = !digitalRead(pinSensorDentro);
  bool estadoBotaoReiniciar = !digitalRead(pinBotaoReiniciar);
  
  //ao apertar o botão, reinicia a contagem
  if (estadoBotaoReiniciar) {
   pessoas = 0; 
  }
  
  //quando o sensor de fora é acionado, 
  //sai do modo de espera e vai pro modo entrando
  if (modo == ESPERA) {
    if (estadoSensorFora) {
      modo = ENTRANDO;
      corLED();
    }
  }
  
  //quando o sensor de dentro é acionado, 
  //sai do modo de espera e vai pro modo saindo
  if (modo == ESPERA) {
    if (estadoSensorDentro) {
      modo = SAINDO;
      corLED();
    }
  }
  
  //após os dois sensores voltarem ao estado normal, 
  //significa que a pessoa já entrou e soma 1 à pessoas
  //e volta ao modo de espera
  if (modo == ENTRANDO) {
    if (!estadoSensorDentro && !estadoSensorFora) {
      pessoas += 1;
      modo = ESPERA;
      corLED();
    }  
  }
  
  //após os dois sensores voltarem ao estado normal, 
  //significa que a pessoa já saiu, subtrai 1 de pessoas 
  //e volta oa modo de espera
  if (modo == SAINDO) {
    if (!estadoSensorDentro && !estadoSensorFora) {
      pessoas -= 1;
      modo = ESPERA;
      corLED();
    }
  }
  
  //printa o valor da variável pessoas no monitor serial
  Serial.println(pessoas);
 
}

void corLED(){
  //se a variável 'pessoas' >= 0 e < limitePessoas,
  //luz verde acesa
  if (limitePessoas >= 0 && pessoas < limitePessoas){
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, HIGH);
    digitalWrite(azul, LOW);
  }
  //se a variável 'pessoas' > limitePessoas,
  //luz vermelha acesa
  else {
    digitalWrite(vermelho, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(azul, LOW);
  }
}
 