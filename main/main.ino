

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns


// Setup keypad 1

char hexaKeysKeypad1[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte colPinsKeypad1[ROWS] = {17, 16, 15, 14};
byte rowPinsKeypad1[COLS] = {21, 20, 19, 18};

// Setup keypad 2

char hexaKeysKeypad2[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte colPinsKeypad2[ROWS] = {25, 24, 23, 22};
byte rowPinsKeypad2[COLS] = {29, 28, 27, 26};




// initialize an instance of class NewKeypad
Keypad keypad1 = Keypad(makeKeymap(hexaKeysKeypad1), rowPinsKeypad1, colPinsKeypad1, ROWS, COLS);
Keypad keypad2 = Keypad(makeKeymap(hexaKeysKeypad2), rowPinsKeypad2, colPinsKeypad2, ROWS, COLS);

int cursorPositionKeypad1 = 0;
int cursorPositionKeypad2 = 0;

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
    0b00000};

byte multiplicationCharacter[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hallo nev :3");

    Serial.begin(9600);

    lcd.createChar(0, multiplicationCharacter);
    lcd.createChar(1, divisionCharacter);
}

void loop()
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):

    char customKey = keypad1.getKey();

    if (customKey)
    {

        // if the end of the line is reached
        if (cursorPositionKeypad1 > 15)
        {
            Serial.println("The end of the line is reached!");
        }

        lcd.setCursor(cursorPositionKeypad1, 1);

        if (customKey == 'A')
        {
            Serial.println(customKey);
            lcd.print("+");
        }
        else if (customKey == 'B')
        {
            lcd.print("-");
        }
        else if (customKey == 'C')
        {
            lcd.write((byte)0);
        }
        else if (customKey == 'D')
        {
            lcd.write((byte)1);
        }
        else if (customKey == '*')
        {
            cursorPositionKeypad1 -= 1;
            lcd.setCursor(cursorPositionKeypad1, 1);
            cursorPositionKeypad1 -= 1;
            lcd.write(" ");
        }
        else if (customKey == '#')
        {
            lcd.write("=");
        }
        else
        {
            // simply print the number
            lcd.print(customKey);
        }

        // increment cursorPositionKeypad1 in order to print the next digit next to this one
        cursorPositionKeypad1 += 1;
    }
}