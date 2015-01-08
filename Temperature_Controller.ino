// LCD Library  
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Download and install TimerOne Library https://arduino-timerone.googlecode.com/files/TimerOne-r11.zip
#include <TimerOne.h>



// Download and install CLickEncoder library https://github.com/0xPIT/encoder
#include <ClickEncoder.h>

ClickEncoder encoder(A0,A1,13,4); // Having trouble with button being A pin...

void timerIsr() {
  encoder.service();
}


// Variables

int target_temp = 0;
int last_temp = 0;

void setup() {

  // Initialize the LCD Library 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Set Temperature: ");
  lcd.print(target_temp);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 

}

void loop() {

  target_temp += encoder.getValue();

  ClickEncoder::Button b = encoder.getButton();
  if ( b != ClickEncoder::Open ) {
    lcd.setCursor(14,1);
    lcd.print("   ");
    lcd.setCursor(14,1);
    lcd.print(b); 
  }

/*  button = digitalRead(13);
  if ( button == LOW ) {
    lcd.setCursor(14,1);
    lcd.print("on"); 
  } else {
    lcd.setCursor(14,1);
    lcd.print("   ");
  }
  */
  if ( target_temp != last_temp ) {
    if ( target_temp <= 0 ) { target_temp = 0; }
    last_temp = target_temp;
    lcd.setCursor(0,0);
    lcd.print("Set Temperature: ");
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0,1);
    lcd.print(target_temp);
    lcd.setCursor(14,1);
    lcd.print("   ");
  }

}

