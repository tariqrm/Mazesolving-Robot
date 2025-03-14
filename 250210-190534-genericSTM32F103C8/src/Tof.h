#define GPIO1 PA0         
#define GPIO2 PA1          
#define GPIO3 PA5
#define GPIO4 PA6
#define GPIO5 PA4

#define SYSRANGE__PART_TO_PART_RANGE_OFFSET 0x024

#define tofAddress1 43
#define tofAddress2 44
#define tofAddress3 45
#define tofAddress4 46
#define tofAddress5 47

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

VL6180X tof1;
VL6180X tof2;
VL6180X tof3;
VL6180X tof4;
VL6180X tof5;

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
bool oledAvailable = true;

void oledSetup(){
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        oledAvailable = false; 
    } else {
        oledAvailable = true; 
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
    }
}

void tofSetup()
{
    pinMode(GPIO1, OUTPUT);
    pinMode(GPIO2, OUTPUT);
    pinMode(GPIO3, OUTPUT);
    pinMode(GPIO4, OUTPUT);
    pinMode(GPIO5, OUTPUT);
    digitalWrite(GPIO1, LOW);
    digitalWrite(GPIO2, LOW);
    digitalWrite(GPIO3, LOW);
    digitalWrite(GPIO4, LOW);
    digitalWrite(GPIO5, LOW);

    Wire.begin();

    digitalWrite(GPIO1, HIGH);
    delay(10);
    tof1.init();
    tof1.configureDefault();
    //tof1.startRangeContinuous();
    tof1.setTimeout(10);
    tof1.setAddress(tofAddress1);

    digitalWrite(GPIO2, HIGH);
    delay(10);
    tof2.init();
    tof2.configureDefault();
    //tof2.startRangeContinuous();
    tof2.setTimeout(10);
    tof2.setAddress(tofAddress2);

    digitalWrite(GPIO3, HIGH);
    delay(10);
    tof3.init();
    tof3.configureDefault();
    //tof3.startRangeContinuous();
    tof3.setTimeout(10);
    tof3.setAddress(tofAddress3);

    digitalWrite(GPIO4, HIGH);
    delay(10);
    tof4.init();
    tof4.configureDefault();
    //tof4.startRangeContinuous();
    tof4.setTimeout(10);
    tof4.setAddress(tofAddress4);

    digitalWrite(GPIO5, HIGH);
    delay(10);
    tof5.init();
    tof5.configureDefault();
    //tof5.startRangeContinuous();
    tof5.setTimeout(10);
    tof5.setAddress(tofAddress5);

    tof1.writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, 125); // L
    tof2.writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, 60);  // LF
    tof3.writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, 107); // C
    tof4.writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, 75);  // RF
    tof5.writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, 125); // R
}

void tofPid()
{
    tof[0] = tof2.readRangeSingleMillimeters();
    tof[2] = tof3.readRangeSingleMillimeters();
    tof[4] = tof4.readRangeSingleMillimeters();
}

void tofStart()
{
    tof[1] = tof1.readRangeSingleMillimeters();
    tof[2] = tof3.readRangeSingleMillimeters();
    tof[3] = tof5.readRangeSingleMillimeters();
}

void tofReadAll()
{
    tof[0] = tof2.readRangeSingleMillimeters();
    tof[1] = tof1.readRangeSingleMillimeters();
    tof[2] = tof3.readRangeSingleMillimeters();
    tof[3] = tof5.readRangeSingleMillimeters();
    tof[4] = tof4.readRangeSingleMillimeters();
}

void printTof()
{
    Serial2.print(tof[0]); //LF
    Serial2.print(",  ");
    Serial2.print(tof[1]); //L
    Serial2.print(",  ");
    Serial2.print(tof[2]); //C
    Serial2.print(",  ");
    Serial2.print(tof[3]); //R
    Serial2.print(",  ");
    Serial2.print(tof[4]); //RF
    Serial2.println();
} 

void displayReadings() {
    
    if (!oledAvailable) return;

    tofReadAll();  
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(20, 10);  
    display.print((int)tof[0]);
    display.setCursor(52, 10);  
    display.print((int)tof[2]);
    display.setCursor(84, 10);  
    display.print((int)tof[4]);
    
    display.setCursor(20, 20);  
    display.print((int)tof[1]);
    display.setCursor(84, 20);
    display.print((int)tof[3]);

    display.setCursor(20, 40);  
    display.print(leftEncoder);
    display.setCursor(84, 40);
    display.print(rightEncoder);
    
    display.display();
}

void printWallState()
{
    Serial2.println("printWallState()");
    for (int i=0; i<3; i++)
    {
        Serial2.print(cellWalls[i]);
        Serial2.print("   ");
    }
    Serial2.println("");
}

void checkWallsCell()
{
    Serial2.println("checkWallsCell()");
    if (x == 0 && y == 0)
    {
        count = 0;
        while(count <10)
        {
            tofStart();
            if (tof[2] <= 190)
            {
            frontWallAvailable = frontWallAvailable + 1;
            }
            else
            {
            frontWallAvailable = frontWallAvailable - 1;
            }
            if (tof[1] <= 150)
            {
            leftWallAvailable= leftWallAvailable + 1;
            }
            else
            {
            leftWallAvailable= leftWallAvailable - 1;
            }
            if (tof[3] <= 150)
            {
            rightWallAvailable= rightWallAvailable + 1;
            }
            else
            {
            rightWallAvailable= rightWallAvailable - 1;
            }
            count = count + 1;
        }
    }
    if (frontWallAvailable >=0 )
    {
        cellWalls[1] =  1;
        F = true;
        //frontWallAvailable = 0;
    }
    else
    {
        cellWalls[1] =  0;
        F = false;
        //frontWallAvailable = 0;
    } 
    if (leftWallAvailable >= 0)
    {
        cellWalls[0] = 1;
        L = true;
        //leftWallAvailable = 0;
    }
    else
    {
        cellWalls[0] = 0;
        L = false;
        //leftWallAvailable = 0;
    }
    if (rightWallAvailable >= 0)
    {
        cellWalls[2] = 1;
        R = true;
        //rightWallAvailable = 0;
    }
    else
    {
        cellWalls[2] = 0;
        R = false;
        //rightWallAvailable = 0;
    }
    printWallState();
    
}


