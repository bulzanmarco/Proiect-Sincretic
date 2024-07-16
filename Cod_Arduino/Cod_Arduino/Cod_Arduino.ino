#include <EEPROM.h>

const int lm35Pin = A0; // Pinul unde este conectat senzorul LM35
const int ledPin = 13;
const int maxMessages = 10; // Numărul maxim de mesaje stocate
const int eepromStart = 1; // Adresa de start în EEPROM pentru mesaje

void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as output
  Serial.begin(9600);
  EEPROM.write(0, 0); // Inițializează numărul de mesaje salvate
}

void loop() {
  // Variabile
  float temperature = readTemperature();

  // Afișează temperatura pe monitorul serial
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Verifică comanda
  if (Serial.available() > 0) {
    char command = Serial.read();

    // ON/OFF LED
    if (command == 'A') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED is ON");
    } else if (command == 'S') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED is OFF");
    } else if (command == 'M') {
      saveMessage();
    } else if (command == 'D') {
      displayMessages();
    } else if (command == 'C') {
      readMessages();
    }
  }

  delay(2000);
}

float readTemperature() {
  int sensorValue = analogRead(lm35Pin); // Citește valoarea de pe pinul analogic
  float voltage = sensorValue * (5.0 / 1023.0); // Convertește valoarea citită în tensiune
  float temperatureC = voltage * 100; // Convertirea tensiunii în temperatură (LM35 are 10 mV/°C)
  return temperatureC;
}

void saveMessage() {
  String message = Serial.readStringUntil('\n'); // Citește mesajul
  int messageLength = message.length();

  if (messageLength > EEPROM.length() - eepromStart - 1) {
    messageLength = EEPROM.length() - eepromStart - 1;
  }

  // Citește numărul curent de mesaje
  int messageCount = EEPROM.read(0);

  // Calculează adresa de start pentru noul mesaj
  int startAddress = eepromStart;
  for (int i = 0; i < messageCount; i++) {
    startAddress += EEPROM.read(startAddress) + 1;
  }

  // Scrie mesajul în EEPROM
  EEPROM.write(startAddress, messageLength);
  for (int i = 0; i < messageLength; i++) {
    EEPROM.write(startAddress + 1 + i, message.charAt(i));
  }

  // Actualizează numărul de mesaje
  messageCount = (messageCount + 1) % maxMessages;
  EEPROM.write(0, messageCount);

  Serial.println("Message saved to EEPROM");
}

void displayMessages() {
  int messageCount = EEPROM.read(0);
  int startAddress = eepromStart;

  Serial.println("Last 10 messages:");
  for (int i = 0; i < messageCount; i++) {
    int messageLength = EEPROM.read(startAddress);
    for (int j = 0; j < messageLength; j++) {
      Serial.print(char(EEPROM.read(startAddress + 1 + j)));
    }
    Serial.println();
    startAddress += messageLength + 1;
  }
}

void readMessages() {
  int messageCount = EEPROM.read(0);
  int startAddress = eepromStart;

  Serial.println("Reading last 10 messages from EEPROM:");
  for (int i = 0; i < messageCount; i++) {
    int messageLength = EEPROM.read(startAddress);
    for (int j = 0; j < messageLength; j++) {
      Serial.print(char(EEPROM.read(startAddress + 1 + j)));
    }
    Serial.println();
    startAddress += messageLength + 1;
  }
}