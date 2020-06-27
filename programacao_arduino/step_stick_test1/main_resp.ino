
void systemInit(){
  LCD_RESET();
  digitalWrite(resetPin,HIGH);  //HIGH to not reset
  digitalWrite(sleepPin,LOW);
  LCD_REFRESH(WELCOME);
}

bool buttonTouchedPageIndexRefresh(uint8_t btPressed){
  if(btPressed == btUP_pressed)  currentPage--;
  if(btPressed == btDOWN_pressed)  currentPage++;


  if(btPressed == btOK_pressed){
    switch(currentPage){
      case HOME1_1:
        currentPage = CONFIGA_1;
        onGoingProcess = false;
        break;
      case HOME1_2:
        currentPage = CONFIGB1_1;
        break;
      case HOME2_1:
        currentPage = PROCESS_W;
        break;
      case CONFIGA_1:
        respHome();
        break;
      case CONFIGA_2:
        aceleracaoProc++;
        if(aceleracaoProc>5) aceleracaoProc=1;
        break;
      case CONFIGB1_1:
        while(digitalRead(btOK)== BUTTONPRESSED);
        setDistancia();

        break;
      case CONFIGB1_2:
        break;
      case CONFIGB2_1:
        velocidadeProc++;
        if(velocidadeProc>5) velocidadeProc=1;
        usePeriodUs = true;
        break;
      case CONFIGB2_2:
        ciclosPorMinuto++;
        if(ciclosPorMinuto>=14) ciclosPorMinuto=8;
        usePeriodUs = false;
        break;
      case PROCESS_W:
        currentPage = PROCESS_G;
        if(!homeMade) respHome();
        onGoingProcess = true;
        break;
      case PROCESS_G:
        currentPage = PROCESS_W;
        onGoingProcess = false;
        break;
      case HOME2_2:
        currentPage = AJUDA_1;
        break;
    }
  }


  
  if(currentPage==0||currentPage==10||currentPage==20||
      currentPage==30||currentPage==40)
                currentPage=HOME1_1;
  if(currentPage==5||currentPage==13||currentPage==25) currentPage--;
}

bool checkButtonTouched(){

  uint8_t btUP_state_temp = digitalRead(btUP);
  uint8_t btOK_state_temp = digitalRead(btOK);
  uint8_t btDOWN_state_temp = digitalRead(btDOWN);
  bool btTouched = false;

   if(btUP_state != btUP_state_temp){
     btUP_state = btUP_state_temp;
     if(btUP_state_temp == BUTTONPRESSED)   buttonTouchedPageIndexRefresh(btUP_pressed);
     btTouched =  true;
   } else   if(btOK_state != btOK_state_temp){
     btOK_state = btOK_state_temp;
     if(btOK_state_temp == BUTTONPRESSED)   buttonTouchedPageIndexRefresh(btOK_pressed);
     btTouched =  true;
   } else   if(btDOWN_state != btDOWN_state_temp){
     btDOWN_state = btDOWN_state_temp;
     if(btDOWN_state_temp == BUTTONPRESSED) buttonTouchedPageIndexRefresh(btDOWN_pressed);
     btTouched =  true;
   } 

   return btTouched;
}



void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(btUP,INPUT); 
  pinMode(btOK,INPUT); 
  pinMode(fcHOME,INPUT); 
  pinMode(btDOWN,INPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(sleepPin,OUTPUT); 
  pinMode(resetPin,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);

  digitalWrite(resetPin,HIGH);  //HIGH to not reset
  digitalWrite(sleepPin,HIGH);
  
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction  
  digitalWrite(LED_BUILTIN, HIGH);

  systemInit();

}


void loop() {
  
  while(1){

  if(onGoingProcess == true) respiratorProcess();
  if(checkButtonTouched()==true){
    
     delay(50);
     digitalWrite(LED_BUILTIN, HIGH);
     delay(50);
     digitalWrite(LED_BUILTIN, LOW);
      
     LCD_REFRESH(currentPage);
    }
  }

  

  respAutoAvanca();
  delay(50); // One second delay




    // CICLO DE RETORNO

  respAutoRecua();
  delay(50); // One second delay


}
