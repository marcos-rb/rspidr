void checkButtonDuringProcess(){  // Yes, I know we should use an interruption. To-do

  uint8_t btUP_state_temp = digitalRead(btUP);
  uint8_t btOK_state_temp = digitalRead(btOK);
  uint8_t btDOWN_state_temp = digitalRead(btDOWN);
  uint8_t fcHOME_state_temp = digitalRead(fcHOME);

  if(btUP_state_temp == BUTTONPRESSED ||
     btOK_state_temp == BUTTONPRESSED ||
     btDOWN_state_temp == BUTTONPRESSED) 
  {
    onGoingProcess = false;
    lcd.setCursor(1, 1);
    lcd.print("  Cancelando...");
    currentPage=PROCESS_W;
  }
  if(!fcHOME_state_temp){
    for(int homeOffset=0; homeOffset<STEPHOMEOFFSET; homeOffset++){
      stepAvanca();
    }
    digitalWrite(dirPin,LOW);
  }
  
}

void turnOnMotor(){
  digitalWrite(resetPin,HIGH);  //HIGH to not reset
  digitalWrite(sleepPin,HIGH);
  
}

void turnOffMotor(){
  digitalWrite(resetPin,HIGH);  //HIGH to not reset
  digitalWrite(sleepPin,LOW);
  
}


void setDistancia(){
  
  if(homeMade == false) respHome();
  int setDistanciaValor = 0;
  LCD_RESET();
  lcd.print("Defina o avanco");
  turnOnMotor();
        
  while(digitalRead(btOK)){
    
    if(!digitalRead(btUP)){
      if(setDistanciaValor < 550){
        stepAvanca();
        setDistanciaValor++;
      } 
      else{
        lcd.setCursor(1, 1);
        lcd.print("Dist. Maxima");
        while(!digitalRead(btUP));
        lcd.setCursor(1, 1);
        lcd.print("            ");
      }
    }
    
    if(!digitalRead(btDOWN)){
      if(setDistanciaValor > 0){
        stepRecua();
        setDistanciaValor--;
      } 
      else{
        lcd.setCursor(1, 1);
        lcd.print("Dist. Minima");
        while(!digitalRead(btDOWN));
        lcd.setCursor(1, 1);
        lcd.print("            ");
      }
    }
  }
  
  lcd.setCursor(1, 1);
  lcd.print("Avanco setado");
  respHome();
  turnOffMotor();
  numerodepassos_avanco = setDistanciaValor;
}

void stepAvanca(){
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(SLOW_STEP_PERIOD); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(SLOW_STEP_PERIOD);
}

void stepRecua(){
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(SLOW_STEP_PERIOD); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(SLOW_STEP_PERIOD);
}


void respHome(){
  turnOnMotor();
  LCD_RESET();
  lcd.print("Executando Home");
  digitalWrite(dirPin,LOW);
  for(int stepTemp = 0; digitalRead(fcHOME); stepTemp++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(HOME_STEP_PERIOD);
    digitalWrite(stepPin,LOW); 
    
    delayMicroseconds(HOME_STEP_PERIOD);

    if(stepTemp>=MAXPASSOERRO) return 0;
  }
  digitalWrite(dirPin,HIGH);
  for(int homeOffset = 0; homeOffset<STEPHOMEOFFSET; homeOffset++){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(HOME_STEP_PERIOD);
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(HOME_STEP_PERIOD);

  }
  
  turnOffMotor();
  homeMade = true;
  
}

void respAutoAvanca(){
  
  // CICLO DE AVANÇO

  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction  
  digitalWrite(LED_BUILTIN, HIGH);

    
  for(int stepTemp = 0; stepTemp < numerodepassos_avanco; stepTemp++) {
    
    digitalWrite(stepPin,HIGH); 
    
    if(stepTemp<passos_aceleracao || stepTemp>(numerodepassos_avanco-passos_aceleracao)) delay(1);
    delayMicroseconds(periodo_us); 
    digitalWrite(stepPin,LOW); 
    
    delayMicroseconds(periodo_us);
    checkButtonDuringProcess();
  }
  


  
  digitalWrite(LED_BUILTIN, LOW);
}


void respAutoRecua(){

  

  digitalWrite(dirPin,LOW); //Retorno
  digitalWrite(LED_BUILTIN, HIGH);
  
  for(int stepTemp = 0; stepTemp < numerodepassos_avanco; stepTemp++) {
    
    digitalWrite(stepPin,HIGH); 
    
    if(stepTemp<passos_aceleracao || stepTemp>(numerodepassos_avanco-passos_aceleracao)) delay(1);
    delayMicroseconds(periodo_us*2);
    digitalWrite(stepPin,LOW); 
    
    delayMicroseconds(periodo_us*2);
    checkButtonDuringProcess();
  }

   digitalWrite(LED_BUILTIN, LOW);
}


void respiratorProcess(){
  if(usePeriodUs){
    periodo_us = 1200 + velocidadeProc*300;
  }
  else{
    periodo_us = 60000000/ (ciclosPorMinuto* numerodepassos_avanco);
    periodo_us = periodo_us/6;  // /2 para o step e /3 pelo ciclo (1 avanco - 2 recua)
  }
  passos_aceleracao = 10 + aceleracaoProc*10;
  

  turnOnMotor();
  while(onGoingProcess){
    respAutoAvanca();
    respAutoRecua();
  }
  turnOffMotor();
  
}
