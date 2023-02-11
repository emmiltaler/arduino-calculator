

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[ROWS] = {17, 16, 15, 14}; // Pins used for the rows of the keypad
byte rowPins[COLS] = {21, 20, 19, 18}; // Pins used for the columns of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int currentCursorPosition = 0;



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


byte divisionCharacter[8] = {   
                0b00000, 
                0b00100, 
                0b00000, 
                0b11111, 
                0b00000, 
                0b00100, 
                0b00000, 
                0b00000    };

byte multiplicationCharacter[8] = {   
                0b00000, 
                0b00000, 
                0b00000, 
                0b00100, 
                0b00000, 
                0b00000, 
                0b00000, 
                0b00000    };


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hallo nev :3");
  
  Serial.begin(9600);

  lcd.createChar(0, multiplicationCharacter);
  lcd.createChar(1, divisionCharacter);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  char customKey = customKeypad.getKey();
    
  if (customKey){

    // if the end of the line is reached
    if (currentCursorPosition > 15) {
        Serial.println("The end of the line is reached!");
    }
    
    lcd.setCursor(currentCursorPosition, 1);

    if (customKey == 'A') {
      Serial.println(customKey);
      lcd.print("+");  
    }
    else if (customKey == 'B') {
      lcd.print("-"); 
    }
    else if (customKey == 'C') {
      lcd.write((byte)0);
    }
    else if (customKey == 'D') {
      lcd.write((byte)1);
    }
    else if (customKey == '*') {
      currentCursorPosition -= 1;
      lcd.setCursor(currentCursorPosition, 1);
      currentCursorPosition -= 1;
      lcd.write(" ");
    }
    else if (customKey == '#') {
      lcd.write("=");
    }
    else {
      // simply print the number  
      lcd.print(customKey);
    }

    // increment currentCursorPosition in order to print the next digit next to this one
    currentCursorPosition += 1;
  }
}
