


#include "definePin.h" // Definition des pins
#include "customCharacters.h"
#include "capteur.h"



void setup(void) {
  #include "Setup.h"
}


// **** Fonction d'interruption ***** //

// interrupt service routine that wraps a user defined function 
// supplied by attachInterrupt
ISR(TIMER5_OVF_vect)
{
  TCNT5 = 3036;  // preload timer
  if(temp_ecran <= TIMOUT)
    temp_ecran++;
}

void interruptBp1()
{
  Bp1 = HIGH;
  temp_ecran = 0;
}

void interruptBp2()
{
  Bp2 = HIGH;
  temp_ecran = 0;
}

void interruptBp3()
{
  Bp3 = HIGH;
  temp_ecran = 0;
}

void interruptBp4()
{
  Bp4 = HIGH;
  temp_ecran = 0;
}

// **************** //
// ***** Main ***** //
// **************** //

void loop(void) {
  
  float temperature = getTemp();
  float ph_voltage = 0.0;

//----- affichage -----
//  Serial.print(temperature);
//  Serial.println("°c");

  lcd.setCursor(0, 1);
  lcd.print("Temperature : " + (String) temperature);
  
  ph_voltage = ((float) analogRead(PHPIN)) * 5.0/1023.0;
  ph = quotientPH_2 * ph_voltage * ph_voltage + ph_voltage * quotientPH + offsetPH; //en V
  lcd.setCursor(0, 2);
  lcd.print("PH : " + (String)ph );

  orp = ((float) analogRead(ORPPIN)) * 5.0/1023.0 *1000 * quotientORP + offsetORP; //en mV
  lcd.setCursor(0, 3);
  lcd.print("ORP : ");
  
  lcd.setCursor(6, 3);
  lcd.print(orp, 0);
  

  if(temp_ecran > TIMOUT)   //off display after timout
  {
    lcd.noBacklight();
    lcd.noDisplay();
  }
  else if(temp_ecran == 0)
  {
    lcd.backlight();
    lcd.display();
  }

  delay(100); //just here to slow down the output so it is easier to read

}

void clearAllBps (){
  Bp1 = LOW;
  Bp2 = LOW;
  Bp3 = LOW;
  Bp4 = LOW;
}
