#define PWMA PB8    //motor driver pins
#define AIN2 PA7
#define AIN1 PA12
#define STBY PA11
#define BIN1 PB0
#define BIN2 PB1
#define PWMB PB9

#define leftOut1 PB12   //interrupt pins of motors 
#define leftOut2 PB13          
#define rightOut1 PB14
#define rightOut2 PB15

#define buzzer PC13
#define switchPin PA8

void setIO()
{
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, HIGH);
    
    pinMode(switchPin, INPUT_PULLUP);
}

void motorDiver()
{
    pinMode(PWMA, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
}

void motorInterrupt()
{
    pinMode(leftOut1, INPUT);
    pinMode(leftOut2, INPUT);
    pinMode(rightOut1, INPUT);
    pinMode(rightOut2, INPUT);
}

void buzz()
{
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
}

void buzzTwice()
{
    digitalWrite(buzzer, LOW);
    delay(75);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
}

void buzzDone()
{
    digitalWrite(buzzer, LOW);
    delay(75);
    digitalWrite(buzzer, HIGH);
    delay(30);
    digitalWrite(buzzer, LOW);
    delay(75);
    digitalWrite(buzzer, HIGH);
    delay(30);
    digitalWrite(buzzer, LOW);
    delay(150);
    digitalWrite(buzzer, HIGH);
}