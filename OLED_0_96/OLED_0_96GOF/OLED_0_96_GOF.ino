// Thư viện và link bài viết tham khảo: http://arduino.vn/bai-viet/1503-gioi-thieu-man-hinh-oled-096-inch-i2c
// https://www.vishay.com/docs/37902/oled128o064dbpp3n00000.pdf
// https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
#include <Wire.h>
#include <GOFi2cOLED.h>

GOFi2cOLED oled;

void setup()
{
  // default slave address is 0x3C
  oled.init(0x3C);  //initialze  OLED display
  oled.display(); // show splashscreen
  delay(2000);
  oled.clearDisplay();

  //oled.setCursor(21, 55);
  //oled.print("Tiktok:@HieuP25");
  //oled.drawRect(0, 7, 127, 63, WHITE);
  //oled.drawLine(0, 7, 127, 7, WHITE);
  //oled.drawLine(0, 0, 120, 0, WHITE);
  //oled.drawPixel(0, 7, WHITE);
  //  oled.drawPixel(40,5,1);
  //oled.display();
  //  delay(3000);

  //  oled.setTextColor(WHITE);
  //  oled.setCursor(0,0);
  //  oled.println("Hello, world!");
  //  oled.println(-1234);
  //  oled.println(3.14159);
  //  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  //  oled.println(3.14159,5);
  //    oled.setTextSize(2);
  //  oled.setTextColor(WHITE);
  //  oled.print("0x"); oled.println(0xDEADBEEF, HEX);
  //  oled.display();
  //  delay(2000);

  //Test send I2C
  //    oled.clearDisplay();
  //    oled.setTextSize(2);
  //    oled.setCursor(5, 30);
  //    oled.println("@HieuP25");
  //    oled.display();
  //    delay(3000);
  //    uint8_t data[] = {0x80, 0x81, 0x80, 0x00};
  //    Wire.beginTransmission(0x3C);
  //    Wire.write(data, 4);
  //    Wire.endTransmission();


}

void loop()
{
  //TODO Something
}
