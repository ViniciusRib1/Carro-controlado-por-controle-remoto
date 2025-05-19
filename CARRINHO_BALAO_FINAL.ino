#include <SoftwareSerial.h>
#include <Servo.h>
#define dir_frent 2
#define dir_atras 3
#define esq_frent 4
#define esq_atras 5
#define debug true
int anguloAtaque = 90;
int anguloRetorno = 0;
SoftwareSerial bt(10,11);
Servo servoMotor;
void setup()
{
    bt.begin(9600);
    Serial.begin(9600);
    servoMotor.attach(13);
    pinMode(dir_frent, OUTPUT);
    pinMode(dir_atras, OUTPUT);
    pinMode(esq_frent, OUTPUT);
    pinMode(esq_atras, OUTPUT);
}
void movimentoRecuada() 
{
    // 1. Move Forward
    //Serial.println("Moving Forward");
    //digitalWrite(dir_frent, HIGH);
    //digitalWrite(esq_frent, HIGH);
    //digitalWrite(esq_atras, LOW);
    //digitalWrite(dir_atras, LOW);
    //delay(300);  

    // 2. Move Backward
    Serial.println("Moving Backward");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, HIGH);
    digitalWrite(dir_atras, HIGH);
    delay(400);

    // 3. Turn Left
    Serial.println("Turning Left");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, HIGH);
    digitalWrite(esq_atras, LOW);
    digitalWrite(dir_atras, LOW);
    delay(110);

    Serial.println("Moving Backward");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, HIGH);
    digitalWrite(dir_atras, HIGH);
    delay(200);

    // 4. Turn Right
    Serial.println("Turning Right");
    digitalWrite(dir_frent, HIGH);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, LOW);
    digitalWrite(dir_atras, LOW);
    delay(110);

    Serial.println("Moving Backward");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, HIGH);
    digitalWrite(dir_atras, HIGH);
    delay(400);

    Serial.println("Turning Right");
    digitalWrite(dir_frent, HIGH);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, LOW);
    digitalWrite(dir_atras, LOW);
    delay(110);

    Serial.println("Moving Backward");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, HIGH);
    digitalWrite(dir_atras, HIGH);
    delay(20);

    Serial.println("Turning Left");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, HIGH);
    digitalWrite(esq_atras, LOW);
    digitalWrite(dir_atras, LOW);
    delay(110);

    // 5. Stop
    Serial.println("Stopping");
    digitalWrite(dir_frent, LOW);
    digitalWrite(esq_frent, LOW);
    digitalWrite(esq_atras, LOW);
    digitalWrite(dir_atras, LOW);
}
void recuada()
{
    char car = Serial.read();
    while (car != 'x') 
    {
        movimentoRecuada();
        car = Serial.read();
    }
}
void loop()
{
    char car = Serial.read();
    if(debug)
    {
        while(car == 'w')
        {
            digitalWrite(dir_frent, HIGH);
            digitalWrite(esq_frent, HIGH);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, LOW);
            car = Serial.read();
        }
        while(car == 's')
        {
            digitalWrite(dir_frent, LOW);
            digitalWrite(esq_frent, LOW);
            digitalWrite(esq_atras, HIGH);
            digitalWrite(dir_atras, HIGH);
            car = Serial.read();
        }
        while(car == 'a')
        {
            digitalWrite(dir_frent, LOW);
            digitalWrite(esq_frent, HIGH);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, LOW);
            car = Serial.read();
        }
        while(car == 'd')
        {
            digitalWrite(dir_frent, HIGH);
            digitalWrite(esq_frent, LOW);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, LOW);
            car = Serial.read();
        }
        while(car == 'x')
        {
            digitalWrite(dir_frent, LOW);
            digitalWrite(esq_frent, LOW);
            digitalWrite(esq_atras, LOW);
            digitalWrite(dir_atras, LOW);
            car = Serial.read();
        }
        while (car == 'l')
        {
            recuada();
            car = Serial.read();
        }
        while(car == 'c')
        {
            int duracao = 90;
            int passos = abs(anguloAtaque - anguloRetorno);
            float tempoPorPasso = (float)duracao / passos;
            for (int i = anguloRetorno; i <= anguloAtaque; i++)
            {
                servoMotor.write(i);
                delay(tempoPorPasso);
            }
            delay(100);
            for (int i = anguloAtaque; i >= anguloRetorno; i--)
            {
                servoMotor.write(i);
                delay(tempoPorPasso);
            }
            car = Serial.read();
        }
    }
}