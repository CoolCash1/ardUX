
/* ____        ____
   |///|       |///|
   |///|       |///|
   |///|       |///|
   |///|____   |///|____    BasicBIOS V1.1
   |///////|   |///////|
   |///////|   |///////|
   --------|   --------|
   BasicBIOS Trademark of [NO_BRAND]
   BasicBios limited NEVER SYKKKKEEEEE
   |-basicBIOS is not a company or even a bios, it is just a joke...


                |-|  |-|  \--\  /--/
                | |  | |   \  \/  /    Alpha
           ARD  | |  | |    >    <       6
                | |__| |   /  /\  \
                 \_____/  /__/  \__\
            ARDUINO'S PC-EQUIVLENT


*/

#include <LiquidCrystal.h>  // include LiquidCrystal libbrary
#include <Servo.h>  // include Servo library (as of alpha R6)

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // setup lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int speakerPin = 6;  // prep speaker

String Version = "Alpha r6";
String BIOSVersion = "1.1";

int siEn = 0;
int animationRunning = 0;
int playSoundReady = 0;
int servoReady = 0;
int servoPin = 0;
int servoRot = 0;

byte backSlash[8] = {
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};

byte bb[8] = {
  B10000,
  B10000,
  B11000,
  B11000,
  B00010,
  B00010,
  B00011,
  B00011
};

byte aniF1[8] = {
  B00010,
  B00100,
  B01000,
  B10001,
  B10001,
  B10001,
  B10101,
  B11111
};

byte aniF2[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B10001,
  B10101,
  B11111,
  B11111
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(1, backSlash);
  lcd.createChar(2, bb);
  lcd.createChar(3, aniF1);
  lcd.createChar(4, aniF2);
  pinMode(speakerPin, OUTPUT);
  tone(speakerPin, 900, 100);
  Serial.println("Welcome To your BasicBIOS PC, press F12 to enter SETUP, or F11 for BOOT_MENU.");
  lcd.setCursor(0, 0);
  lcd.write(2);
  lcd.setCursor(1, 0);
  lcd.print(" BasicBIOS");
  lcd.setCursor(0, 1);
  lcd.print("f12 for Setup");
  delay(2500);
  tone(speakerPin, 900, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Version");
  lcd.setCursor(7, 0);
  lcd.print(BIOSVersion);
  lcd.setCursor(0, 1);
  lcd.print("Loading OS...");
  Serial.println("Loading Operating System from boot device ARDUINO_INTERNAL_MEMORY, look at iDisplay for more info.");
  Serial.println("all text from this point on is from the OS, Bye Bye...");
  delay(2500);
  lcd.clear();
  delay(2500);
  lcd.print("ardux is loading");
  Serial.println("OS: ardUX_ALPHA is loading... Look at iDisplay");
  delay(750);
  lcd.clear();
  lcd.print("ardUX ");
  lcd.setCursor(6, 0);
  lcd.print(Version);
  tone(speakerPin, 250, 500);
  delay(500);
  tone(speakerPin, 500, 500);
  delay(500);
  tone(speakerPin, 1000, 500);
  lcd.setCursor(7, 1);
  delay(500);
  lcd.print("|");
  lcd.setCursor(7, 1);
  delay(750);
  lcd.print("/");
  lcd.setCursor(7, 1);
  delay(750);
  lcd.print("-");
  lcd.setCursor(7, 1);
  delay(750);
  lcd.write(1);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ardUX ");
  lcd.setCursor(6, 0);
  lcd.print(Version);
  lcd.setCursor(0, 1);
  lcd.print("Arduino@admin#:");
  lcd.setCursor(15, 1);
}

void loop() {
  if (animationRunning == 0) {
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }
  if (playSoundReady == 1) {
    if (Serial.available()  > 0) {
      int Note = Serial.read();
      Note = Note - 48;
      Serial.print("OS: Return = ");
      Serial.println(Note);
      Note = map(Note, 0, 10, 0, 1000);
      tone(speakerPin, Note, 9999);
      Serial.print("OS: ");
      Serial.print("playing frequency ");
      Serial.print(Note);
      Serial.println(" for 10 seconds");
      delay(10000);
      playSoundReady = 0;
    }
  }
 // if (servoReady == 1) {
 //   if (Serial.available()  > 0) {
 //     servoPin = Serial.read();
 //     constrain(servoPin, 7, 10);
      
 //   }
 // }
if (Serial.available()  > 0) {
    String incomingCMD = Serial.readString();
    if (incomingCMD == "animation 1") {
      animationRunning = 1;
      Serial.print("OS: animationRunning == ");
      Serial.println(animationRunning);
    }
    if (incomingCMD == "animation 0") {
      animationRunning = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ardUX ");
      lcd.setCursor(6, 0);
      lcd.print(Version);
      lcd.setCursor(0, 1);
      lcd.print("Arduino@admin#:");
      lcd.setCursor(15, 1);
      Serial.print("OS: animationRunning == ");
      Serial.println(animationRunning);
    }
    if (incomingCMD == "Version") {
      Serial.print("OS: ardUX Version: ");
      Serial.println(Version);
    }
    if (incomingCMD == "playSound") {
      playSoundReady = 1;
      Serial.println("OS: type note frequency / 100 (0-9 only)");
    }
    if (incomingCMD == "servoMove") {
      //servoReady = 1;
      Serial.println("OS: Feature not yet avalible");
    }
  }
  if (animationRunning == 1) {
    lcd.noCursor();
    lcd.clear();
    lcd.write(3);
    tone(speakerPin, 250, 100);
    delay(1000);
    lcd.clear();
    lcd.write(4);
    tone(speakerPin, 1000, 100);
    delay(1000);
  }
}
