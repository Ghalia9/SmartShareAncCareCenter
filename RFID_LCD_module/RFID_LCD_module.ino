#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RST_PIN  9 // RES pin
#define SS_PIN  10 // SDA (SS) pin
String tagID = "";
byte readCard[4];
MFRC522 mfrc522(SS_PIN, RST_PIN);

boolean cardScanned = false;
unsigned long displayTimer = 0;
unsigned long displayDuration = 3000; // 5 seconds

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  //mfrc522.PCD_DumpVersionToSerial();
  //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Please scan");
  lcd.setCursor(0, 1);
  lcd.print("your card!");
}

void loop() {
  if (!cardScanned) {
    if (getID()) {
       
        cardScanned = true;
              Serial.print(tagID); // Send tagID over Serial

        displayTimer = millis();
    }
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - displayTimer >= displayDuration) {
      cardScanned = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please scan");
      lcd.setCursor(0, 1);
      lcd.print("your card!");
    }
  }
  if (Serial.available()) {
    
    byte dataBytes[32]; // Allocate a buffer for the incoming data
   int numBytes = Serial.readBytes(dataBytes, 32); // Read up to 32 bytes of data
    String dataString;
    for (int i = 0; i < numBytes; i++) {
      dataString += (char)dataBytes[i]; // Convert the byte to a character and append it to the string
    }
    
    dataString.trim(); 

        if (dataString.startsWith("true")) { // If the incoming data starts with "true"
      String name = dataString.substring(4); // Extract the name from the incoming data (assuming the name starts at index 5)
      lcd.clear(); // Clear the screen
      lcd.setCursor(0,0); // Set the cursor to the top-left corner of the screen
      lcd.print("Access granted!"); // Display "Access granted!" on the screen
      lcd.setCursor(0,1); // Set the cursor to the second row of the screen
      lcd.print("Welcome: " + name); // Display the name of the user on the second row of the screen
    } else if (dataString.startsWith("false")) { // If the incoming data starts with "false"
      lcd.clear(); // Clear the screen
      lcd.setCursor(0,0); // Set the cursor to the top-left corner of the screen
      lcd.print("Access denied."); // Display "Access denied." on the screen
      lcd.setCursor(0,1); // Set the cursor to the second row of the screen
      lcd.print("Please try again."); // Display "Please try again." on the second row of the screen
    }
      
}
}
boolean getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";

  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}
