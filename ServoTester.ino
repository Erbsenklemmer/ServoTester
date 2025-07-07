#include <U8g2lib.h>
#include <Wire.h>

#include <Bounce2.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, PIN_A5, PIN_A4);

//#include "Adafruit_SSD1306.h"

//Adafruit_SSD1306 display(1);

int count(0);
volatile byte EncoderStatus = 200;

int previousMilis = 0;
int displayUpdateMilis = 250;

int currentPos = 0;
int pressedState = 0;

Bounce2::Button button;

#define BUTTON_HOLD 1000

void setup() {
  Serial.begin(9600);

  pinMode(PIN3, INPUT_PULLUP);
  pinMode(PIN4, INPUT_PULLUP);

  button.attach(PIN5, INPUT_PULLUP);
  button.interval(5);

  display.begin();
  display.setFontDirection(0);
  display.setFontRefHeightExtendedText();

  display.setDrawColor(1);
  display.setFontPosTop();

  display.clearDisplay();
  display.display();

  attachInterrupt(digitalPinToInterrupt(PIN3), Encoder, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

  button.update();


  pressedState = 0;
  if (button.changed()) {
    if (button.isPressed() != LOW) {
      if (button.previousDuration() < BUTTON_HOLD) {
        Serial.println("Short klick");
        pressedState = 1;
      } else {
        Serial.println("Long klick");
        pressedState = 2;
      }
    } else
      Serial.println("Start pressing");
    Serial.print("Pressed: ");
    Serial.println(pressedState);
  }

  //if (millis() - previousMilis > displayUpdateMilis)
  {
    //Serial.println("UpdateDisplay");
    display.clearBuffer();

    display.setFont(u8g2_font_6x10_tf);

    display.drawStr(0, 0, "drawBox");
    display.drawBox(5, 10, 20, 10);

    display.drawStr(60, 0, "drawFrame");
    display.drawFrame(65, 10, 20, 10);

  int i = currentPos;
    String posOut = String(i, 10);
    //display.drawStr(20, 40, posOut.c_str());

    Serial.println(posOut);

    display.setFont(u8g2_font_helvB14_te);

    display.drawStr(20, 40, posOut.c_str());

    // String pressedStr;
    // if (pressedState == 1)
    //   pressedStr = "short";
    // else if (pressedState == 2)
    //   pressedStr = "long";

    //display.drawStr(60, 40, pressedStr.c_str());
    
    // //display.drawUTF8(20, 40, h.c_str());
    // Serial.println(pressedStr);

    display.sendBuffer();

    // if (millis() - previousMilis > displayUpdateMilis) {
    //   previousMilis = millis();
    //   pressedState = "";
    // }

    if (EncoderStatus != 200) {
      if (EncoderStatus & B00010000)
        currentPos--;
      else
      {
        currentPos++;
      }

      EncoderStatus = 200;
    }
  }
}

void Encoder() {
  EncoderStatus = PIND;
}