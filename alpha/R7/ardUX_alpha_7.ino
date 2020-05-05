
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
           ARD  | |  | |    >    <       7
                | |__| |   /  /\  \
                 \_____/  /__/  \__\
               ARDUINO'S PC-EQUIVLENT


*/

#include <LiquidCrystal.h>  // include LiquidCrystal libbrary
#include <Servo.h>  // include Servo library (as of alpha R6)

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // setup lcd

const int speakerPin = 6;  // prep speaker

String Version = "Alpha r7"; //string for the version name, Used for cosmetics only
String BIOSVersion = "1.1";  //string for the "BIOS" version name, Used for cosmetics only

int animationRunning = 0;  //int used to keep track of the animation command
int playSoundReady = 0;  //int used for playSound Setup
int servoReady = 0;  //int used for servoReady Setup
int servoPin = 0;  //int to keep track of user-defined servo pin
int servoRot = 0;  //int to keep track of user-defined servo rotation (Not Used)

int servoPinS = 0;


byte backSlash[8] = {  //Backslash graphic
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};

byte bb[8] = {  //BasicBIOS bb graphic
  B10000,
  B10000,
  B11000,
  B11000,
  B00010,
  B00010,
  B00011,
  B00011
};

byte aniF1[8] = {  //the first frame of the animation (graphic)
  B00010,
  B00100,
  B01000,
  B10001,
  B10001,
  B10001,
  B10101,
  B11111
};

byte aniF2[8] = {  //the second frame of the animation (graphic)
  B00000,
  B00000,
  B00000,
  B11111,
  B10001,
  B10101,
  B11111,
  B11111
};

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //create LCD Object
Servo S1;  //create Servo Object

void setup() {
  Serial.begin(9600);  //engage serial commuincation
  lcd.begin(16, 2);  //initiate LCD Object
  lcd.createChar(1, backSlash);  //initiate graphics
  lcd.createChar(2, bb);  
  lcd.createChar(3, aniF1); 
  lcd.createChar(4, aniF2);
  pinMode(speakerPin, OUTPUT);  //initiate speaker
  tone(speakerPin, 900, 100);  //play first startup "beep"
  Serial.println("Welcome To your BasicBIOS PC, press F12 to enter SETUP, or F11 for BOOT_MENU.");
  lcd.setCursor(0, 0);  //print bb graphic at 0,0
  lcd.write(2);
  lcd.setCursor(1, 0);  //print " BasicBIOS" at 1, 0
  lcd.print(" BasicBIOS");
  lcd.setCursor(0, 1);  //print "f12 for Setup" at 0, 1
  lcd.print("f12 for Setup");
  delay(2500);
  tone(speakerPin, 900, 100);  //play second startup beep
  lcd.clear();  
  lcd.setCursor(0, 0);  //print version to LCD
  lcd.print("Version");
  lcd.setCursor(7, 0);  //print Loading OS messages
  lcd.print(BIOSVersion);
  lcd.setCursor(0, 1);
  lcd.print("Loading OS...");
  Serial.println("Loading Operating System from boot device ARDUINO_INTERNAL_MEMORY, look at iDisplay for more info.");
  Serial.println("all text from this point on is from the OS, Bye Bye...");
  delay(2500);
  lcd.clear();
  delay(2500);
  lcd.print("ardux is loading");  //print ardUX startup messages
  Serial.println("OS: ardUX_ALPHA is loading... Look at iDisplay");
  delay(750);
  lcd.clear();
  lcd.print("ardUX "); //print Version
  lcd.setCursor(6, 0);
  lcd.print(Version);
  tone(speakerPin, 250, 500);  //play the classic startup sound
  delay(500);
  tone(speakerPin, 500, 500);
  delay(500);
  tone(speakerPin, 1000, 500);
  lcd.setCursor(7, 1);  //play loading animation
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
  lcd.setCursor(0, 0);  //some lcd text to improve looks
  lcd.print("ardUX ");
  lcd.setCursor(6, 0);
  lcd.print(Version);
  lcd.setCursor(0, 1);
  lcd.print("Arduino@admin#:");
  lcd.setCursor(15, 1);
}

void loop() {
  if (animationRunning == 0) {  //if animation is not running flash the cursor
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }
  if (playSoundReady == 1) {  //if playsound is ready for execution and serial is available, play the sound for 10 seconds
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
  if (servoReady == 1) {  //first stage of the servoRedy Command, reciving the servo's pin
    if (Serial.available()  > 0) {
      servoPinS = Serial.read() - 48;
      Serial.println(servoPinS);
      constrain(servoPin, 7, 9);
      servoReady = 2;
      Serial.println("OS: Type the location you want to move the servo to (0-180)");
    }
  }
  if (servoReady == 2) {  //second stage of th servoReady Command, reciving the servo's desired rotation and moving it there.
    if (Serial.available() > 0) {
      String LocationS = Serial.readString();
      int Location = LocationS.toInt();
      Serial.println(Location);
      S1.attach(servoPinS);
      S1.write(Location);
      servoReady = 0;
    }
  }
  if (Serial.available()  > 0) {  //check if serial is available, this is the starting point for all commands
    String incomingCMD = Serial.readString();  //if the incomming command is animation 1, enable animation
    if (incomingCMD == "animation 1") {
      animationRunning = 1;
      Serial.print("OS: animationRunning == ");
      Serial.println(animationRunning);
    }
    if (incomingCMD == "animation 0") {  //if the incomming command is animation 0, diable animation
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
    if (incomingCMD == "Version") {  //if the incomming command is Version, Print the Version
      Serial.print("OS: ardUX Version: ");
      Serial.println(Version);
    }
    if (incomingCMD == "playSound") {  //if the incomming command is playSound, prepare for playing a sound
      playSoundReady = 1;
      Serial.println("OS: type note frequency / 100 (0-9 only)");
    }
    if (incomingCMD == "servoMove") {  //if the incomming command is servoMove, prepare to movr a servo
      servoReady = 1;
      Serial.println("OS: Type the pin your Servo is on");
    }
  }
  if (animationRunning == 1) {  //script to control animation
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
