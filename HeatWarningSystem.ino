#include <LiquidCrystal_I2C.h>;

// Replace with your Wi-Fi credentials
//const char* ssid = SECRET_SSID;
//const char* password = SECRET_PASS;

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address may vary; use the correct address for your LCD

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

}

void loop() {

  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100;
  //float temperature = 106; //We can change this value for testing purposes

  int roundedTemp = (int)temperature;

  String tempStr = String(roundedTemp);
  tempStr = tempStr + "F";

if (temperature > 50 && temperature < 95){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(6, 1);
  lcd.print(tempStr);
  delay(10000);
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Nice and");
  lcd.setCursor(4,1);
  lcd.print("Comfy!");
  delay(10000);
}
else if (temperature > 95 && temperature < 105){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(6, 1);
  lcd.print(tempStr);
  delay(5000);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("High Risk");
  lcd.setCursor(2,1);
  lcd.print("of Heatstroke");
  delay(5000);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Hydrate");
  lcd.setCursor(4,1);
  lcd.print("Often");
  delay(5000);

  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Stay");
  lcd.setCursor(4,1);
  lcd.print("Inside");
  delay(5000);
}
else if (temperature > 105){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(6, 1);
  lcd.print(tempStr);
  delay(5000);

  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("DANGER");
  lcd.setCursor(2,1);
  lcd.print("STAY INSIDE");
  delay(10000);
}

else {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(6, 1);
  lcd.print(tempStr);
  delay(10000);
}

}