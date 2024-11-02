#include <limits.h>
#include <LiquidCrystal.h>
#include <avr/eeprom.h>

// Eeprom Class Implementation
class Eeprom {
  public:
    Eeprom(){}
    
    // Method to read a byte from EEPROM at a specific address
    byte read(unsigned int uiAddress) {
      // Wait for completion of previous write
      while (EECR & (1 << EEPE));
      
      // Set up address register
      EEAR = uiAddress;
      
      // Start EEPROM read by writing EERE
      EECR |= (1 << EERE);
      
      // Return the data from the data register
      return EEDR;
    }
    
    // Method to write a byte to EEPROM at a specific address
    void write(unsigned int uiAddress, unsigned char data) {
      // Wait for completion of previous write
      while (EECR & (1 << EEPE));
      
      // Set up address register
      EEAR = uiAddress;
      // Set up data register
      EEDR = data;
      
      // Write logical 1 to EEMPE to enable master write
      EECR |= (1 << EEMPE);
      
      // Start EEPROM write by setting EEPE
      EECR |= (1 << EEPE);
    }
};

// Button Class Implementation
class Button {
  public:
    // Constructor for button initialization
    Button(unsigned short pin) : buttonPin(pin), debounceDelay(50), lastDebounceTime(0) {
      pinMode(buttonPin, INPUT);
    }

    // Method to check if the button was pushed with debouncing
    bool hasBeenPushed() {
      bool buttonState = digitalRead(buttonPin);
      unsigned long currentTime = millis();
      
      // Check if button state has changed and debounce
      if (buttonState && (currentTime - lastDebounceTime > debounceDelay)) {
        lastDebounceTime = currentTime; // Update last debounce time
        return true;
      }
      return false;
    }

  private:
    unsigned short buttonPin;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;  
};

// Constants
const unsigned short EEPROM_START_ADDRESS = 0;
const unsigned short MAX = USHRT_MAX;
const unsigned short MIN = 10000;

// LCD Pins: rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Eeprom eeprom;
Button button(8);  // Assume the button is connected to pin 8

unsigned short tokens[10];
unsigned long lastTokenChange = 0;
unsigned int currentTokenIndex = 0;

// Function to generate and store tokens
void generateTokens() {
  for (int i = 0; i < 10; i++) {
    // Generate a random number between MIN and MAX
    unsigned short token = random(MIN, MAX);
    
    // Store the token in EEPROM by splitting into high and low bytes
    byte highByte = (token >> 8) & 0xFF; // High bits (8-15)
    byte lowByte = token & 0xFF;         // Low bits (0-7)
    
    eeprom.write(EEPROM_START_ADDRESS + (i * 2), highByte);
    eeprom.write(EEPROM_START_ADDRESS + (i * 2) + 1, lowByte);
  }
}

// Function to read token from EEPROM
unsigned short readTokenFromEEPROM(int index) {
  byte highByte = eeprom.read(EEPROM_START_ADDRESS + (index * 2));
  byte lowByte = eeprom.read(EEPROM_START_ADDRESS + (index * 2) + 1);
  
  return (highByte << 8) | lowByte;  // Combine the high and low bytes
}

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.clear();
  
  // Seed the random number generator
  randomSeed(analogRead(0));

  // Generate and store the tokens in EEPROM
  generateTokens();
}

void loop() {
  // Check if the button has been pushed
  if (button.hasBeenPushed()) {
    // Read the current token from EEPROM
    unsigned short token = readTokenFromEEPROM(currentTokenIndex);
    
    // Display the token on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Hardware Token");
    lcd.setCursor(0, 1);
    lcd.print(token);
    
    // Wait for 3 seconds, then clear the LCD
    delay(3000);
    lcd.clear();
  }
  
  // Update token every 10 seconds
  if (millis() - lastTokenChange > 10000) {
    lastTokenChange = millis();
    
    // Move to the next token (wrap around after 10 tokens)
    currentTokenIndex = (currentTokenIndex + 1) % 10;
  }
}
