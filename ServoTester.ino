#include <U8g2lib.h>
#include <Wire.h>

#include <EncoderTool.h>
#include <Bounce2.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, PIN_A5, PIN_A4);

//#include "Adafruit_SSD1306.h"

//Adafruit_SSD1306 display(1);

int count(0);
EncoderTool::PolledEncoder encoder;
Bounce2::Button button;

#define BUTTON_HOLD 1000

void setup() {
  Serial.begin(9600);

  //encoder.begin(2, 3);
  encoder.begin(PIN2, PIN3);//, PIN4);

  button.attach(PIN4, INPUT_PULLUP);
  button.interval(5);

  

  // display.begin(SSD1306_SWITCHCAPVCC, 60);

  // display.setTextColor(WHITE);

  // display.clearDisplay();

  // display.fillRect(10, 10, 20, 55, WHITE);

  display.begin();
  display.setFontDirection(0);
  display.setFontRefHeightExtendedText();

  display.setFont(u8g2_font_6x10_tf);
  display.setDrawColor(1);
  display.setFontPosTop();

  display.clearBuffer();
  display.drawStr(0, 0, "drawBox");

  display.drawBox(5, 10, 20, 10);

  display.drawStr(60, 0, "drawFrame");
  display.drawFrame(65, 10, 20, 10);

  display.sendBuffer();
}

void loop() {
  // put your main code here, to run repeatedly:
  encoder.tick();
  button.update();
  //display.clearBuffer();
  //display draw something
  //display.updateDisplayArea(x, y, w, h);

  if (encoder.valueChanged()) {
    Serial.println(encoder.getValue());
  }
  if (encoder.buttonChanged())
  {
    Serial.print("ENCODER button state: ");
    Serial.println(encoder.getButton() == LOW ? "pressed" : "released");
  }
  // if (button.changed())  // do we have a new button state?
  // {
  //   Serial.print("button state: ");
  //   Serial.println(button.isPressed() == LOW ? "pressed" : "released");
  //   Serial.print("previous duration: ");
  //   Serial.println(button.previousDuration());
  // }

  if (button.changed())
  {
    if (button.isPressed() != LOW)
    {
      if (button.previousDuration() < BUTTON_HOLD)
        Serial.println("Short klick");
      else
        Serial.println("Long klick");
    }
    // else
    //   Serial.println("Start pressing");
  }

  // Serial.print("Hallo3 ");
  // Serial.println(count);
  // count++;
  // delay(250);
}
