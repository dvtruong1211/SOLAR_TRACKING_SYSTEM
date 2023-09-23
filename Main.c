#include <Servo.h>
#include <math.h>

Servo myservo1, myservo2;
int LDR1 = A0, LDR2 = A1, LDR3 = A2, LDR4 = A3;
int rRDL1 = 0, rRDL2 = 0, rRDL3 = 0, rRDL4 = 0;
int max1=0, max2=0, max3=0;
int ser1 = 80, ser2=0;
float tmp2;
int x = 0;
int dataPin = 2; //DIO
int latchPin = 3; //RCK
int clockPin = 5; //SCK
unsigned char Ledcode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void setup()
{
    myservo1.attach(9);
    myservo2.attach(8);
    Serial.begin(9600);
    myservo1.write(ser1);
    myservo2.write(ser2);
    pinMode(dataPin,OUTPUT);
    pinMode(latchPin,OUTPUT);
    pinMode(clockPin,OUTPUT);
}
void loop()
{
    rRDL1 = analogRead(LDR1) / 100;
    rRDL2 = analogRead(LDR2) / 100;
    rRDL3 = analogRead(LDR3) / 100;
    rRDL4 = analogRead(LDR4) / 100;
    max1 = max(rRDL1, rRDL2);
    max2 = max(rRDL3, rRDL4);
    max3 = max(max1, max2);
    if(rRDL1<max3 && rRDL2<max3)
    {
        if(ser1>0)
            ser1-=1;
        myservo1.write(ser1);
    }

    if(rRDL3<max3 && rRDL4<max3)
    {
        if(ser1<160)
            ser1+=1;
        myservo1.write(ser1);
    }
    if(rRDL2<max3 && rRDL3<max3)
    {
        if(ser2<180)
            ser2+=1;
        myservo2.write(ser2);
    }
    if(rRDL1<max3 && rRDL4<max3)
    {
        if(ser2>0)
            ser2-=1;
        myservo2.write(ser2);
    }
        int tmp1 = analogRead(A4);
        tmp2 = (float)tmp1 /1023 *5 ;
        hienthi(tmp2*11*100);
    }
    void showAdigit(int number, int value, int dot)
    {
    int tmp;
    tmp = Ledcode[value];
    if(dot == 1) tmp &= 0x7F;
    switch(number)
    {
    case 0:
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST,tmp );
        shiftOut(dataPin , clockPin, MSBFIRST, 0x01);
        digitalWrite(latchPin, HIGH);
        break;
    case 1:
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST,tmp );
        shiftOut(dataPin , clockPin, MSBFIRST, 0x02);
        digitalWrite(latchPin, HIGH);
        break;
    case 2:
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST,tmp );
        shiftOut(dataPin , clockPin, MSBFIRST, 0x04);
        digitalWrite(latchPin, HIGH);
        break;
    case 3:
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST,tmp );
        shiftOut(dataPin , clockPin, MSBFIRST, 0x08);
        digitalWrite(latchPin, HIGH);
        break;
    }
}
void hienthi(int number){
    int a, b, c, d;
    a = number / 1000;
    b = (number % 1000) / 100;
    c = (number % 100) / 10;
    d = number % 10;
    for(int i = 0; i < 5; i++)
    {
        showAdigit(0, d, 0);
        delay(1);
        showAdigit(1, c, 0);
        delay(1);
        showAdigit(2, b, 1);
        delay(1);
        showAdigit(3, a, 0);
        delay(1);
    }
}