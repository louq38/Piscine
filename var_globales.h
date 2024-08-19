
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

//----- Adressage matériel -----
//lcd
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4);


volatile boolean Bp1 = LOW;
volatile boolean Bp2 = LOW;
volatile boolean Bp3 = LOW;
volatile boolean Bp4 = LOW;
volatile byte temp_ecran = 0;

float ph = 0.0;
float offsetPH = 0.13; // V
float quotientPH = 3.5;
float quotientPH_2 = 0.0;
boolean PHcalibrated = false;

float orp = 0.0;
float offsetORP = 100; //mV
float quotientORP = 1.0;
