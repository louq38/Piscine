//capteur.h
#include <OneWire.h> //for the temp sensor
#include "var_globales.h"

//Temperature chip i/o
OneWire ds(TEMP_PIN);  // on digital pin 2

float getTemp();
void calibrationPH();



float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  ds.reset(); //  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9;  i++  ) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}


void calibrationPH()
{
  float cal7=0.0, cal3=0.0, cal9=0.0;
  float xA =7.0, xB =3.0, xC =9.0;

  clearAllBps();
  
  lcd.setCursor(0, 0);
  lcd.print("Calibration PH ");

  lcd.setCursor(18, 3);
  lcd.print("OK");

  lcd.setCursor(12, 3);
  lcd.print("Cancel");


//deux points :

  if(cal3 != 0 && cal7 != 0 && PHcalibrated == false){
    
    quotientPH = (cal7-cal3)/(xB-xA);
    offsetPH = cal7-xA*quotientPH;
    
    PHcalibrated = true;  
    lcd.setCursor(0, 0);
    lcd.print("Pente : "+String(quotientPH,2));
    lcd.setCursor(0, 1);
    lcd.print("Ord : " + String(offsetPH,2)); 
    lcd.setCursor(0, 2);
    lcd.print("pH-metre calibre");
  }

//trois points :

  if(cal3 != 0 && cal7 != 0 && cal9 != 0 && PHcalibrated == false){
    
    quotientPH_2 = (cal9 - cal7) / ((xC - xA) * (xC - xB)) - (cal3 - cal7) / ((xB - xA) * (xC - xB)); //a=(yC−yA) /{(xC−xA)(xC−xB)} − (yB−yA)/{(xB−xA)(xC−xB)} 
    quotientPH = (cal3 - cal7)/(xB-xA) - quotientPH_2 * (xB - xA) ; //b=(yB−yA)/(xB−xA) −a(xB+xA)
    offsetPH = cal7 - quotientPH*xA*xA - quotientPH*xA; //c=yA−ax2A−bxA
    
    PHcalibrated = true;  
    lcd.setCursor(0, 0);
    lcd.print("a : "+String(quotientPH_2,2));
    lcd.setCursor(0, 1);
    lcd.print("b : " + String(quotientPH,2)); 
    lcd.setCursor(0, 2);
    lcd.print("c : " + String(offsetPH,2)); 
    lcd.setCursor(0, 2);
    lcd.print("pH calibre");
    }

 
}

float calx( int nb)
{
  lcd.setCursor(0,1);
  lcd.print("avec la solution a " + (String) nb);
  
  ReadPH();
  
  return();
}

float ReadPH()
{
  int buf[10];
  float avgValue=0.0;
  
  analogRead(PHPIN);
  for(int i=0;i<10;i++) //10 mesures
  {
  buf[i]=analogRead(PHPIN);
  delay(10);
  }
  
  for(int i=0;i<10;i++) // moyenne
  {
  avgValue+=(float) buf[i];
  }
  avgValue/=10;
  return avgValue;
}
