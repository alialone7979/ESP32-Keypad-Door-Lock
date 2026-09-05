#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

int rs = 23, en = 2, d4 = 25, d5 = 26, d6 = 27, d7 = 32;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

Servo myservo;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {4, 5, 16, 17}; // Rows
byte colPins[COLS] = {18, 19, 21, 22}; // Columns

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correctPassword ="1379";
String enteredPassword = "";

void setup() {
  myservo.attach(13);
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
  myservo.write(0);
}

void loop() {

  char key = keypad.getKey();
  if (key) {
   if(key =='C') {
    enteredPassword = "";
    lcd.clear();
    lcd.print("Enter Password:");
    lcd.setCursor(0,1);
   }
    else if (key == 'D')
   {
    checkPassword();
   }
    else if (isdigit(key))
   {
     if (enteredPassword.length() < 4 )
     {
      enteredPassword += key;
      lcd.print("*");
     }
   }
  }
}
 void checkPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (enteredPassword == correctPassword) {
     myservo.write(90);
    lcd.print("Correct! :)"); // Password matches
    lcd.setCursor(0,1);
    lcd.print("Door is Open!");
    delay(3000);
    myservo.write(0);
  } else {
    lcd.print("Wrong! :("); // Password incorrect
    lcd.setCursor(0,1);
    lcd.print("Door is Close!");
  }

  delay(2000); // Show result for 2 seconds
  // Reset for next attempt
  enteredPassword = "";
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
}