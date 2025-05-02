// inclusão de bibliotecas que darão o suporte necessário para a execução do código 
#include <SoftwareSerial.h>
#include <Servo.h>
#define motor_1 12
#define dir_frent 4
#define dir_atras 5
#define motor_2 13
#define esq_frent 6
#define esq_atras 7
#define Farol 8
#define Lanterna 9
#define debug true


// definição dos ângulos do servo
#define angulo_atacar   90
#define angulo_recolher 10

SoftwareSerial bt(10, 11);

Servo servo;  // declaração da variável que corresponderá ao servo motor

// inicializa RX e TX do bluetooth 


// Funções utilizadas pelo código abaixo
bool nenhumNovoComando();
void rencolheBracoSeTempo();
void atacaBracoSeTempo();
void setUltimoTempo(unsigned long long int ult);

// Definição das configurações iniciais
void setup()
{
    servo.attach(3);      // inicialização do servo motor no pino 3
    bt.begin(9600);       // inicialização do componente bluetooth
    Serial.begin(9600);   // inicialização das portas seriais
    pinMode(motor_1, OUTPUT);
    pinMode(motor_2, OUTPUT);
    pinMode(dir_frent, OUTPUT);
    pinMode(dir_atras, OUTPUT);
    pinMode(esq_frent, OUTPUT);
    pinMode(esq_atras, OUTPUT);
    pinMode(Farol, OUTPUT);
    digitalWrite(Lanterna, OUTPUT);
    digitalWrite(Farol,HIGH);
    digitalWrite(Lanterna,HIGH);
    delay(1000);
    digitalWrite(Farol,LOW);
    digitalWrite(Lanterna,LOW);
    delay(1000);
    
}

// Função onde está o código será executado continuamente
void loop()
{
    if( nenhumNovoComando() )
    {
        /*digitalWrite(dir_frent, LOW);
        digitalWrite(dir_atras, LOW);
        digitalWrite(esq_frent, LOW);
        digitalWrite(esq_atras, LOW);*/
    }

    rencolheBracoSeTempo();

    char ch;
    if(debug){
      switch(Serial.read())               // "carrega" o valor da variável ch, se ela for igual a alguns dos casos abaixo elo codigo será executado
        {
        case 'b':
            atacaBracoSeTempo();
            Serial.print("Ataquei!");
            break;
            
        case 'w':
            Serial.print("Frente");

            analogWrite(motor_1, 255);
            analogWrite(motor_2, 255);
            digitalWrite(dir_frent, HIGH);
            digitalWrite(esq_frent, HIGH);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, LOW);
            break;
            
        case 's':
            Serial.print("Atras!");

            analogWrite(motor_1, 255);
            analogWrite(motor_2, 255);
            digitalWrite(dir_frent, LOW);
            digitalWrite(esq_frent, LOW);
            digitalWrite(esq_atras, HIGH);
            digitalWrite(dir_atras, HIGH);
            break;
            
        case 'a':
            Serial.print("Esquerda");

            analogWrite(motor_1, 255);
            analogWrite(motor_2, 255);
            digitalWrite(dir_frent, LOW);
            digitalWrite(esq_frent, HIGH);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, HIGH);
            break;
            
        case 'd':
            Serial.print("Direita");

            analogWrite(motor_1, 255);
            analogWrite(motor_2, 255);
            digitalWrite(dir_frent, HIGH);
            digitalWrite(esq_frent, LOW);
            digitalWrite(esq_atras, HIGH);
            digitalWrite(dir_atras, LOW);
            break;

         case 'x':
            Serial.print("Acende Farol");
            digitalWrite(Farol, HIGH);
            digitalWrite(Lanterna, HIGH);
            delay(1000);
            break;

         case 'c':
            Serial.print("Desliga farol");
            digitalWrite(Farol, LOW);
            digitalWrite(Lanterna, LOW);
            break;
            
        default:
            setUltimoTempo(0);
        }
    }
}



// ==================== NÃO MODIFICAR ====================
bool ataque=false;
unsigned long long int ultimo=0, servot=0;
// Funções de controle da "arma"
bool nenhumNovoComando() {
    return millis()-ultimo > 5000;
}
void rencolheBracoSeTempo() {
    if (ataque && millis()-servot > 500) {
        servo.write(angulo_atacar);
        ataque = false;
    }
}
void atacaBracoSeTempo() {
    if(!ataque && millis()-servot > 1000) {
        ataque = true;
        servo.write(angulo_recolher);
        servot = millis();
    }
}
void setUltimoTempo(unsigned long long int ult) {
    ultimo = ult;
}
// ==================== NÃO MODIFICAR ====================