/*
Ports:
  0 0 .. 13 13 .. 53 53
  Uno: A0: 14, A1: 15, A2: 16, A3: 17: A4: 18: A5: 19: A6: 20, A7: 21
  Mega: A0: 54, A1: 55, A2: 56, A3: 57: A4: 58: A5: 59: A6: 60, A7: 61...
  port bits: 5 ... 0..32
  0:   0: 00000
  1:   1: 00001
  A7: 21: 10101
*/

#include <Arduino.h>
#include <Wire.h>

#define DEBUG // remove debug so pin 0 and 1 can be used for IO
//#define DEBUG_READ // more advanced debuging

#define I2C_ADDRESS 8 //i2c starts at pin 8

void onRequest();
void onReceive(int);

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println(F("Init "));
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    analogReference(INTERNAL1V1);
#endif
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    analogReference(INTERNAL);
#endif

  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(onRequest);
  Wire.onReceive(onReceive);

#ifdef DEBUG
  Serial.println(F("Wire ok"));
#endif
}

void loop()
{
  //int temp = analogRead(A1);
  //Serial.println(temp);
}

volatile byte buffer[9];
volatile byte len = 1;

#define DIGITAL_READ(b, pin, mask) \
  if (digitalRead(pin))            \
    buffer[b] |= mask;

void readDigital()
{
  len = 9;
  buffer[0] = 0;
  buffer[1] = 0;
  buffer[2] = 0;
  buffer[3] = 0;
  buffer[4] = 0;
  buffer[5] = 0;
  buffer[6] = 0;
  buffer[7] = 0;
  buffer[8] = 0;
  
  DIGITAL_READ(0, 0, 1); //0
  DIGITAL_READ(0, 1, 2); //1
  DIGITAL_READ(0, 2, 4); //2
  DIGITAL_READ(0, 3, 8); //3
  DIGITAL_READ(0, 4, 16); //4
  DIGITAL_READ(0, 5, 32); //5
  DIGITAL_READ(0, 6, 64); //6
  DIGITAL_READ(0, 7, 128); //7

  DIGITAL_READ(1, 8, 1); //8
  DIGITAL_READ(1, 9, 2); //9
  DIGITAL_READ(1, 10, 4); //10
  DIGITAL_READ(1, 11, 8); //11
  DIGITAL_READ(1, 12, 16); //12
  DIGITAL_READ(1, 13, 32); //13

//Arduino Mega Boards
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  DIGITAL_READ(1, 14, 64); //14
  DIGITAL_READ(1, 15, 128); //15

  DIGITAL_READ(2, 16, 1); //16
  DIGITAL_READ(2, 17, 2); //17
  DIGITAL_READ(2, 18, 4); //18
  DIGITAL_READ(2, 19, 8); //19
  DIGITAL_READ(2, 19, 16); //20 Not avaliable on Arduino Mega, i2c pin.
  DIGITAL_READ(2, 19, 32); //21 Not avaliable on Arduino Mega, i2c pin.
  DIGITAL_READ(2, 22, 64); //22
  DIGITAL_READ(2, 23, 128); //23

  DIGITAL_READ(3, 24, 1); //24
  DIGITAL_READ(3, 25, 2); //25
  DIGITAL_READ(3, 26, 4); //26
  DIGITAL_READ(3, 27, 8); //27
  DIGITAL_READ(3, 28, 16); //28
  DIGITAL_READ(3, 29, 32); //29
  DIGITAL_READ(3, 30, 64); //30
  DIGITAL_READ(3, 31, 128); //31

  DIGITAL_READ(4, 32, 1); //32
  DIGITAL_READ(4, 33, 2); //33
  DIGITAL_READ(4, 34, 4); //34
  DIGITAL_READ(4, 35, 8); //35
  DIGITAL_READ(4, 36, 16); //36
  DIGITAL_READ(4, 37, 32); //37
  DIGITAL_READ(4, 38, 64); //38
  DIGITAL_READ(4, 39, 128); //39

  DIGITAL_READ(5, 40, 1); //40
  DIGITAL_READ(5, 41, 2); //41
  DIGITAL_READ(5, 42, 4); //42
  DIGITAL_READ(5, 43, 8); //43
  DIGITAL_READ(5, 44, 16); //44
  DIGITAL_READ(5, 45, 32); //45
  DIGITAL_READ(5, 46, 64); //46
  DIGITAL_READ(5, 47, 128); //47

  DIGITAL_READ(6, 48, 1); //48
  DIGITAL_READ(6, 49, 2); //49
  DIGITAL_READ(6, 50, 4); //50
  DIGITAL_READ(6, 51, 8); //51
  DIGITAL_READ(6, 52, 16); //52
  DIGITAL_READ(6, 53, 32); //53
  DIGITAL_READ(6, A0, 64); //54
  DIGITAL_READ(6, A1, 128); //55

  DIGITAL_READ(7, A2, 1); //56
  DIGITAL_READ(7, A3, 2); //57
  DIGITAL_READ(7, A4, 4); //58
  DIGITAL_READ(7, A5, 8); //59
  DIGITAL_READ(7, A6, 16); //60
  DIGITAL_READ(7, A7, 32); //61
  DIGITAL_READ(7, A8, 64); //62
  DIGITAL_READ(7, A9, 128); //63

  DIGITAL_READ(8, A10, 1); //64
  DIGITAL_READ(8, A11, 2); //65
  DIGITAL_READ(8, A12, 4); //66
  DIGITAL_READ(8, A13, 8); //67
  DIGITAL_READ(8, A14, 16); //68
  DIGITAL_READ(8, A15, 32); //69
#endif

// Arduino Uno Boards
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  DIGITAL_READ(1, A0, 64); //14
  DIGITAL_READ(1, A1, 128); //15

  DIGITAL_READ(2, A2, 1); //16
  DIGITAL_READ(2, A3, 2); //17
  //DIGITAL_READ(2, A4, 4); //Not avaliable on Arduino Uno, i2c pin.
  //DIGITAL_READ(2, A5, 8); //Not avaliable on Arduino Uno, i2c pin.
  DIGITAL_READ(2, A6, 16); //20
  DIGITAL_READ(2, A7, 32); //21
#endif

// DIGITAL READ not supports on A3 .. A7 on Arduino Uno
#ifdef DEBUG_READ
  Serial.print(F("Read 9 bytes: "));
  Serial.print(buffer[0]);
  Serial.print(' ');
  Serial.print(buffer[1]);
  Serial.print(' ');
  Serial.println(buffer[2]);
  Serial.print(' ');
  Serial.println(buffer[3]);
  Serial.print(' ');
  Serial.println(buffer[4]);
  Serial.print(' ');
  Serial.println(buffer[5]);
  Serial.print(' ');
  Serial.println(buffer[6]);
  Serial.print(' ');
  Serial.println(buffer[7]);
  Serial.print(' ');
  Serial.println(buffer[8]);
#endif
}
void readAnalog(int pin)
{
  int val = analogRead(A0 + pin);
  len = 2;
  buffer[0] = val & 0xFF;
  buffer[1] = (val >> 8) & 0b11;
#ifdef DEBUG_READ
  Serial.print(F("Read analog pin "));
  Serial.println(pin);
#endif
}

void onRequest()
{
  Wire.write(const_cast<uint8_t *>(buffer), len);
}

#define CMD_DIGITAL_READ 0x0

#define CMD_WRITE_ANALOG 0x2
#define CMD_WRITE_DIGITAL_HIGH 0x3
#define CMD_WRITE_DIGITAL_LOW 0x4

#define CMD_SETUP_PIN_OUTPUT 0x5
#define CMD_SETUP_PIN_INPUT_PULLUP 0x6
#define CMD_SETUP_PIN_INPUT 0x7

// 8 analog registers.. A0 to A14
// A4 and A5 on Arduino Uno are not supported due to I2C
#define CMD_ANALOG_READ_A0 0b1000 // 0x8
// ....
#define CMD_ANALOG_READ_A14 0b10000 //16

#define CMD_SETUP_ANALOG_INTERNAL 0x10
#define CMD_SETUP_ANALOG_DEFAULT 0x12

void onReceive(int numBytes)
{
#ifdef DEBUG_READ
  Serial.print("Received bytes: ");
  Serial.println(numBytes);
#endif
  int cmd = Wire.read();

  switch (cmd)
  {
  case CMD_DIGITAL_READ:
    readDigital();
    break;
  }

  if (cmd >= CMD_ANALOG_READ_A0 && cmd <= CMD_ANALOG_READ_A14)
  {
    readAnalog(cmd & 0b1110);
    return;
  }

  int pin = Wire.read();

  switch (cmd)
  {
  case CMD_WRITE_DIGITAL_HIGH:
  case CMD_WRITE_DIGITAL_LOW:
  {
    bool output = cmd == CMD_WRITE_DIGITAL_HIGH;
    digitalWrite(pin, output);
#ifdef DEBUG
    Serial.print(F("Pin "));
    Serial.print(pin);
    Serial.println(output ? F(" HIGH") : F(" LOW"));
#endif
    break;
  }
  case CMD_WRITE_ANALOG:
  {
    int val = Wire.read() & (Wire.read() << 8);
    analogWrite(pin, val);
#ifdef DEBUG
    Serial.print(F("Pin "));
    Serial.print(pin);
    Serial.print(F(" Analog write "));
    Serial.println(val);
#endif
    break;
  }
  case CMD_SETUP_PIN_OUTPUT:
    pinMode(pin, OUTPUT);
#ifdef DEBUG
    Serial.print(F("Pin "));
    Serial.print(pin);
    Serial.println(F(" OUTPUT"));
#endif
    break;
  case CMD_SETUP_PIN_INPUT:
    pinMode(pin, INPUT);
#ifdef DEBUG
    Serial.print(F("Pin "));
    Serial.print(pin);
    Serial.println(F("INPUT"));
#endif
    break;
  case CMD_SETUP_PIN_INPUT_PULLUP:
    pinMode(pin, INPUT_PULLUP);
#ifdef DEBUG
    Serial.print(F("Pin "));
    Serial.print(pin);
    Serial.println(F("INPUT PULLUP"));
#endif
    break;
  case CMD_SETUP_ANALOG_INTERNAL:

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    analogReference(INTERNAL1V1);
#endif
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    analogReference(INTERNAL);
#endif
#ifdef DEBUG
    Serial.println(F("Analog reference INTERNAL"));
#endif
    break;
  case CMD_SETUP_ANALOG_DEFAULT:
    analogReference(DEFAULT);
#ifdef DEBUG
    Serial.println(F("Analog reference DEFAULT"));
#endif
    break;
  }
}
