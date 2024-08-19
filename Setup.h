// Setup.h

//  Serial.begin(19200);

//----- initialisation des IO -----//
  pinMode(BP1,INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(BP1), interruptBp1, FALLING);
  pinMode(BP2,INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(BP2), interruptBp2, FALLING);
  pinMode(BP3,INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(BP3), interruptBp3, FALLING);
  pinMode(BP4,INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(BP4), interruptBp4, FALLING);
  
  pinMode(ACT1,OUTPUT);
  pinMode(ACT2,OUTPUT);
  pinMode(ACT3,OUTPUT);
  pinMode(ACT3,OUTPUT);
  digitalWrite(ACT1,HIGH);
  digitalWrite(ACT2,HIGH);
  digitalWrite(ACT3,HIGH);
  digitalWrite(ACT4,HIGH);
  
//----- initialisation du LCD -----//
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Piscinometre");

   // Create new characters:
  lcd.createChar(0, Aigu);
  lcd.createChar(1, Grave);
  lcd.createChar(2, Fleche);


// ----- initialize timer5 ----- //
  noInterrupts();           // disable all interrupts
  TCCR5A = 0;
  TCCR5B = 0;

  TCNT5 = 3036;            // preload timer 65536-16MHz/256/1Hz
  TCCR5B |= (1 << CS12);    // 256 prescaler 
  TIMSK5 |= (1 << TOIE5);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
