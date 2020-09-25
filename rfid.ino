#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

String stringOne, stringTwo,stringThree, stringFour, stringFive;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);


  stringOne = String("F9");
  stringTwo = String("81");
  stringThree = String("4A");
  stringFour = String("73");
  stringFive= String();
  
  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(7,OUTPUT);
 
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

stringFive = stringOne + stringTwo + stringThree + stringFour;
Serial.println(stringFive);


  // Dump debug info about the card; PICC_HaltA() is automatically called
  Serial.println("Card Detected");
  digitalWrite(7,1);
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  digitalWrite(7,0);

  while(true);
}
