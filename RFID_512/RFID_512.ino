#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>;

#define RST_PIN         5
#define SS_PIN          53
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();         //Khởi động màn hình.
  lcd.backlight();    //Bật đèn nền
  SPI.begin();        //Thiết lập SPI
  mfrc522.PCD_Init(); //Khởi tạo rfid
  delay(4);
}

void loop() {
  //Hàm check hiện tại có card đang cần xử lý không
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  //Hàm check xem Card này có thể đọc được không
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Set vị trí hiển thị UUID, côt 0 hàng 0
  lcd.setCursor(0, 0);
  //In chuỗi UID: lên lcd
  lcd.print("UID:");
  lcd.setCursor(4, 0);
  //In mã UID nhận được từ hàm getUID()
  String id = getUID(); 
  lcd.print(id);
  Handle(id);
  delay(1500);
  lcd.clear();
}

//Hàm lấy giá trị UID của card
String getUID() {
  String ret;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10)
      ret += " 0";
    else
      ret += " ";
    ret += String(mfrc522.uid.uidByte[i], HEX);
  }
  ret.toUpperCase();
  return ret;
}
//Hàm xử lý khi nhận diện được UID card
void Handle(const String& uid) {
  //Làm bất cứ việc gì trong dự án của bạn
  //Ví dụ:
  //- Kích hoạt đóng mở cửa bằng relay
  //- Chấm công, quản lý thời gian ra vào
  //- Check vé xe...
  if (uid.equals(" E8 B7 4D 0D")) {
    lcd.setCursor(1, 1);
    lcd.print("Hello HieuP25");
  } else {
    lcd.setCursor(3, 1);
    lcd.print("Hello guest");
  }
}
