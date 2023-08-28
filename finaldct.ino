#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "arduinoFFT.h"

#define EL 82.41                //Frequency of each string on guitar from E Low to E High.
#define A 110.
#define D 146.83
#define G 196.
#define B 246.94
#define EH 329.63

#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.

int buttonarray[] = {2, 3, 4, 5, 6, 7}; // [EL, A2, D3, G3, B3, EH]
int i, button;
float stringFrequency , freqDiff;
double peak;
bool tuned, el, a, d, g, b, eh;
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
unsigned int samplingPeriod;
unsigned long microSeconds;

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 4);
arduinoFFT FFT = arduinoFFT();
void setup()
{
  for (int i = 0; i <= 5; i++)
  {
    pinMode(buttonarray[i], INPUT);
  }
  Serial.begin(115200); //Baud rate for the Serial Monitor
  lcd.init();
  lcd.backlight();
  myServo.attach(8);
  samplingPeriod = round(1000000 * (1.0 / SAMPLING_FREQUENCY)); //Period in microseconds
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  lcd.begin(16, 2);
}

void loop()
{
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  for (int s = 0; s <= 5; s++)
  {
    if (digitalRead(buttonarray[s]) == HIGH)
    {
      button = s;
      digitalWrite(9, HIGH);
      break;
    }
  }

  printString();

  switch (button) {
    case 1:
      el = false;
      stringFrequency = EL;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          el = true;
        }
      } while (el != true);
      break;

    case 2:
      a = false;
      stringFrequency = A;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          a = true;
        }
      } while (a != true);
      break;
    case 3:
      d = false;
      stringFrequency = D;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          d = true;
        }
      } while (d != true);
      break;
    case 4:
      g = false;
      stringFrequency = G;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          g = true;
        }
      } while (g != true);
      break;
    case 5:
      b = false;
      stringFrequency = B;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          b = true;
        }
      } while (b != true);
      break;
    case 6:
      eh = false;
      stringFrequency = EH;
      do {
        measureFreq();
        Serial.println(peak);
        freqDiff = peak - stringFrequency;

        if (freqDiff < -1)
        {
          digitalWrite(12, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          myServo.write(360);
          delay(-20 * freqDiff);
          myServo.writeMicroseconds(1500);
        }
        else if (freqDiff > 5)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
          myServo.write(0);
          delay(20 * freqDiff);
          myServo.writeMicroseconds(1500);

        }
        else
        {
          digitalWrite(10, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(9, LOW);
          delay(2000);
          eh = true;
        }
      } while (eh != true);
      break;
    default:
      stringFrequency = 0;
      break;
  }
  
  Serial.println(el);
  Serial.println(a);
  Serial.println(d);
  Serial.println(g);
  Serial.println(b);
  Serial.println(eh);
}

void measureFreq()
{
  for (int i = 0; i < SAMPLES; i++)
  {
    microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script.

    vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always

    /*remaining wait time between samples if necessary*/
    while (micros() < (microSeconds + samplingPeriod))
    {
      //do nothing
    }
  }

  /*Perform FFT on samples*/
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  /*Find peak frequency and print peak*/
  peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
}

void printString()
{
  if (button == 0)
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("E2 string");

  }

  else if (button == 1)
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("A string");
  }

  else if (button == 2)
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("D string");
  }

  else if (button == 3)
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("G string");
  }

  else if (button == 4)
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("B string");
  }

  else
  {
    lcd.clear();
    lcd.print("You selected the");
    lcd.setCursor(1, 1);
    lcd.print("E4 string");
  }
}
