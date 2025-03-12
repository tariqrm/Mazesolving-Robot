void stbyHigh()
{
    digitalWrite(STBY, HIGH);
}

void stbyLow()
{
    digitalWrite(STBY, LOW);
}

void leftForward()
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
}

void leftReverse()
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
}

void leftBrake()
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
}

void leftForwardBase()
{
    stbyHigh();
    leftForward();
    analogWrite(PWMA, leftBase/2);
}

void leftReverseBase()
{
    stbyHigh();
    leftReverse();
    analogWrite(PWMA, leftBase/2);
}

void rightForward()
{
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
}

void rightReverse()
{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
}

void rightBrake()
{
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
}

void rightForwardBase()
{
    stbyHigh();
    rightForward();
    analogWrite(PWMB, rightBase/2);
}

void rightReverseBase()
{
    stbyHigh();
    rightReverse();
    analogWrite(PWMB, rightBase/2);
}

void writePwm()
{
    analogWrite(PWMA, leftPwm/2);
    analogWrite(PWMB, rightPwm/2);
}

void writeBasePwm()
{
    analogWrite(PWMA, leftBase/2);
    analogWrite(PWMB, rightBase/2);
}

void forward()
{
    stbyHigh();
    leftForward();
    rightForward();
    writePwm();
}

void reverse()
{
    stbyHigh();
    leftReverse();
    rightReverse();
    writePwm();
}

void brake()
{
    stbyHigh();
    leftBrake();
    rightBrake();
    delay(75);
}

void brakeNo()
{
    stbyHigh();
    leftBrake();
    rightBrake();
    //delay(100);
}

void forwardBase()
{
    stbyHigh();
    leftForward();
    rightForward();
    writeBasePwm();
}

void reverseBase()
{
    stbyHigh();
    leftReverse();
    rightReverse();
    writeBasePwm();
}

void turnRight()
{
    stbyHigh();
    leftForward();
    rightReverse();
    writeBasePwm();
}

void turnLeft()
{
    stbyHigh();
    leftReverse();
    rightForward();
    writeBasePwm();
}
