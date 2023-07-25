#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>;
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define BUF_SIZE    75

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint16_t scrollSpeed = 70;
textEffect_t textEffect = PA_SCROLL_LEFT;
textEffect_t newEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
char curMessage[BUF_SIZE] = {0};
char newMessage[BUF_SIZE] = { "Hello HieuP25" };
bool newParamAvailable = true;

void readSerial(void)
{
  uint32_t pos = 0;
  String s = "";
  while (Serial1.available())
  {
    s = Serial1.readString();
  }
  if (s.length() > 0) {
    Serial.println(s);
    // Get Action
    if (s.startsWith("[SPD]") && s.endsWith("#")) {
      String temp = s.substring(5, s.length() - 1);
      scrollSpeed = atoi(temp.c_str());
      Serial.println("Action change speed: " + String(scrollSpeed));
    }
    else if (s.startsWith("[ANM]")) {
      int randomNum = random(1, 29);
      newEffect = randomNum;
      Serial.println("Action change Animation: " + String(randomNum));
    }
    else {
      strncpy(newMessage, s.c_str(), BUF_SIZE - 1);
      Serial.println("Action chane Display: " + String(newMessage));
    }
    newParamAvailable = true;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  P.begin();
  P.setIntensity(1);
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, textEffect, textEffect);
}

void loop()
{
  if (P.displayAnimate())
  {
    if (newParamAvailable)
    {
      if (P.getSpeed() != scrollSpeed) {
        P.setSpeed(scrollSpeed);
        Serial1.println("Set Speed: " + String(P.getSpeed()));
      }
      if (strlen(newMessage) > 0) {
        Serial1.println("Set Display: " + String(newMessage));
        strcpy(curMessage, newMessage);
        memset(newMessage, 0, sizeof(newMessage));
      }
      if (textEffect != newEffect) {
        textEffect = newEffect;
        Serial1.println("Set TextEffect: " + String(textEffect));
        P.setTextEffect(textEffect, textEffect);
      }
      newParamAvailable = false;
    }
    P.displayReset();
  }
  readSerial();
}
