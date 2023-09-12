#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);      // Đợi Serial Monitor hiển thị
  Serial.println("I2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  //  Định địa chỉ I2C có 7 bit ứng với 128 thiết bị, việc quét sẽ tiến hành
  //  từ 1 tới 127 (1 thiết bị làm master (là địa chỉ bus I2C) nên chỉ còn 127)
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
      Serial.println("Device no. " + String(nDevices));
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("number of devices " + String(nDevices));

  delay(5000);  // Delay 5s cho quá trình scan tiếp theo
}
