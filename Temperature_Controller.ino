// LCD Library  
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Adafruit Thermo-sensor

#include "Adafruit_MAX31855.h"
Adafruit_MAX31855 thermocouple(3, 4, 5);


// Download and install TimerOne Library https://arduino-timerone.googlecode.com/files/TimerOne-r11.zip
#include <TimerOne.h>


// Download and install CLickEncoder library https://github.com/0xPIT/encoder
#include <ClickEncoder.h>

ClickEncoder encoder(A0,A1,13,4); // Having trouble with button being A pin...

void display_temperature () {
  lcd.clear();
  lcd.print("Temp = ");
  lcd.println(thermocouple.readInternal() );
}

void timerIsr() {
  encoder.service();
}


// Variables

int target_temp = 0;
int last_temp = 0;

enum op_state { OFF = 0, SET_TEMP, RUN };
op_state state = OFF;

void set_temperature () {

  // Initialize display for set_temperature state.
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Temperature: ");

  ClickEncoder::Button b = encoder.getButton();
  while ( b != 5 ) {
    b = encoder.getButton();

    target_temp += encoder.getValue();
      if ( target_temp != last_temp ) {
        if ( target_temp <= 0 ) { target_temp = 0; }
        last_temp = target_temp;
        lcd.setCursor(0,1);
        lcd.print("    ");
        lcd.setCursor(0,1);
        lcd.print(target_temp);
      } // End if
  } // End while

  state = RUN;

} // End set_temperature

void run() {
  
    lcd.clear();
  ClickEncoder::Button b = encoder.getButton();
  
  while ( b != 5 ) {
    b = encoder.getButton();
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print( thermocouple.readInternal() );
    lcd.setCursor(0,1);
    lcd.print("Target = ");
    lcd.print(target_temp);
  }
    delay(3000);
//  state = OFF;
} // End run


void setup() {

  lcd.begin(16,2);
  lcd.print("Initializing....");
  lcd.setCursor(0,1);
  lcd.print("  Vulcanizer");
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 

  delay(300);
  
}


void loop() {
                    // Clear Display
  lcd.clear();       

  switch ( state ) {
    case OFF:
      set_temperature();
      break;
    case RUN:
      run();
      break;
  }
  
}                

