// Code mẫu sử dung thư viện
#include <LCD595.h>

LCD595 lcd(9, 10, 8); // data, SH_CP, ST_CP,

void setup() {
  lcd.begin();
  lcd.print("   PhamHieuuu");
}


void loop() {
  lcd.setCursor(0, 1);
  lcd.print("   Time: ");
  lcd.print(millis() / 1000);
  lcd.print("s");
  delay(500);

}
