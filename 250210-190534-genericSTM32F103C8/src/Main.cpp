#include <Arduino.h>

#define Serial2 Serial2

#include <VL6180X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <EEPROM.h>

#include "Pins.h"
#include "ZlgoVariables.h"
#include "Variables.h"
#include "Tof.h"
#include "Motors.h"
#include "Turns.h"
#include "WallPid.h"
#include "Speed.h"
#include "Moves.h"
#include "Zlgo.h"
#include "MazeSolve.h"

void setup()
{   
    stbyHigh();
    tofSetup();
    setIO();
    oledSetup();
    motorDiver();
    motorInterrupt();
    
    attachInterrupt(digitalPinToInterrupt(PB12), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB13), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB14), countRightOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB15), countRightOut1, RISING);
    
    Serial2.begin(9600);
    Serial2.println("setup()");
}

void loop()
{
    //cellForward();
    //brake();
    //delay(10000);
    
    //displayReadings();
    
    //wallFollow();
    
    //delay(5000);
    //rightAboutTurn();

    //delay(5000);
    //leftAboutTurn();
    
    delay(1000);
    searchStates();
    
}
