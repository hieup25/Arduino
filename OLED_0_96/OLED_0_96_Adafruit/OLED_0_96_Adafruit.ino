// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HCSR04.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define DELAY 1000 // ms

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
HCSR04 hcsr04;

void setup() {
  // Kết nối đến OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    /* Kết nối thất bại, loop không thực hiện tiếp chương trình */
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  /* Kết nối thành công, bắt đầu setup các thông số */
  display.clearDisplay(); // Xóa buffer lưu trữ các giá trị pixel trong thư viện
  display.setTextSize(1); // Đặt kích thước văn bản là 1x (rộng 6 pixel, cao 8 pixel)
  display.setTextColor(SSD1306_WHITE); // Đặt màu sắc của văn bản là trắng
  delay(DELAY);
  /*  Vẽ 1 hình chữ nhật bo góc
      tham số truyền vào gồm:
      x bắt đầu vẽ, y bắt đầu vẽ, chiều dài,
      chiều cao, số pixel bo góc, màu chữ
  */
  display.drawRoundRect(0, 0, display.width(),
                        display.height(), 5, SSD1306_WHITE);
  /* Hiển thị 1 văn bản
     hàm setCursor để đặt con trỏ tại x, y
     để bắt đầu viết ký tự tại vị trí đó
  */
  display.setCursor((display.width() / 2) - (16 * 6 / 2),
                    display.height() - 10);
  display.println(F("TikTok: @HieuP25"));

  /* Hiển thị 1 văn bản, với kích thước 2
     hàm setCursor để đặt con trỏ tại x, y
     để bắt đầu viết ký tự tại vị trí đó
  */
  display.setTextSize(2);
  display.setCursor((display.width() / 2) - (8 * 12 / 2), 5);
  display.println(F("Distance"));
  display.display(); // Phải gọi hàm display() này để hiển thị văn bản lên OLED
}

void loop() {
  /* Hiển thị giá trị khoảng cách từ mpdule HCSR04 */
  String distance = hcsr04.getDistance() + String(" cm");
  display.setCursor((display.width() / 2) - (distance.length() * 12 / 2), 28);
  display.println(distance);
  display.display();
  delay(500);
  display.fillRect((display.width() / 2) - (distance.length() * 12 / 2), 28,
                   distance.length() * 12, 16, 0);
}
