//LCD processes
void LCD_RESET(){
  
  lcd.clear();
  lcd.setCursor(0, 0);
}

void LCD_REFRESH(int PageIndex){

  
  refreshFlag = false;
  while(refreshFlag == false){
    LCD_RESET();
    switch(PageIndex){
      case WELCOME:
        lcd.print("  Bem vindo");
        lcd.setCursor(0, 1);
        lcd.print(VERSAO);
        delay(2000);
        PageIndex++;
        break;
        
      case HOME1_1:
        lcd.print("->Set Aparato   ");
        lcd.setCursor(0, 1);
        lcd.print("  Set Prcsso  ..");
        refreshFlag = true;
        break;
        
      case HOME1_2:
        lcd.print("  Set Aparato   ");
        lcd.setCursor(0, 1);
        lcd.print("->Set Prcsso  ..");
        refreshFlag = true;
        break;

      case HOME2_1:
        lcd.print("->Iniciar     ..");
        lcd.setCursor(0, 1);
        lcd.print("  Ajuda         ");
        refreshFlag = true;
        break;
      
      case HOME2_2:
        lcd.print("  Iniciar     ..");
        lcd.setCursor(0, 1);
        lcd.print("->Ajuda         ");
        refreshFlag = true;
        break;

      case CONFIGA_1:
        lcd.print("->Ex. Home      ");
        lcd.setCursor(0, 1);
        lcd.print("  Acc: ");
        lcd.print(aceleracaoProc);
        refreshFlag = true;
        break;

      case CONFIGA_2:
        lcd.print("  Ex. Home      ");
        lcd.setCursor(0, 1);
        lcd.print("->Acc: ");
        lcd.print(aceleracaoProc);
        refreshFlag = true;
        break;
        
      case CONFIGB1_1:
        lcd.print("->Set Offset    ");
        lcd.setCursor(0, 1);
        lcd.print("  Pp Ccl ");
        lcd.print(aceleracaoProc);
        lcd.setCursor(14, 1);
        lcd.print("..");
        refreshFlag = true;
        break;

      case CONFIGB1_2:
        lcd.print("  Set Offset    ");
        lcd.setCursor(0, 1);
        lcd.print("->Pp Ccl ");
        lcd.print(aceleracaoProc);
        lcd.setCursor(14, 1);
        lcd.print("..");
        refreshFlag = true;
        break;
        
      case CONFIGB2_1:
        lcd.print("->Vlcd ");
        lcd.print(velocidadeProc);  
        if(usePeriodUs){
          lcd.setCursor(12, 0);
          lcd.print("<-");
        }
        lcd.setCursor(14, 0);
        lcd.print("..");
        lcd.setCursor(0, 1);
        lcd.print("  Ciclo ");
        
        lcd.print(ciclosPorMinuto);
        if(!usePeriodUs){
          lcd.setCursor(12, 1);
          lcd.print("<-");
        }
        refreshFlag = true;
        break;

      case CONFIGB2_2:
        lcd.print("  Vlcd ");
        lcd.print(velocidadeProc);
        if(usePeriodUs){
          lcd.setCursor(12, 0);
          lcd.print("<-");
        }
        lcd.setCursor(14, 0);
        lcd.print("..");
        lcd.setCursor(0, 1);
        lcd.print("->Ciclo ");
        lcd.print(ciclosPorMinuto);
        if(!usePeriodUs){
          lcd.setCursor(12, 1);
          lcd.print("<-");
        }
        refreshFlag = true;
        break;
        
      case PROCESS_W:
        lcd.print("Inicia processo?");
        lcd.setCursor(0, 1);
        lcd.print("   Aperte OK    ");
        refreshFlag = true;
        break;
        
      case PROCESS_G:
        lcd.print("  Em andamento  ");
        lcd.setCursor(0, 1);
        lcd.print(" ");
        refreshFlag = true;
        break;

      case AJUDA_1:
        lcd.print(VERSAO);
        lcd.setCursor(0, 1);
        lcd.print(" ");
        refreshFlag = true;
      break;

        default:
        PageIndex=HOME1_1;
        currentPage=HOME1_1;
        break;
       
    }

  } 

  while(digitalRead(btOK) == BUTTONPRESSED);
  while(digitalRead(btUP) == BUTTONPRESSED);
  while(digitalRead(btDOWN) == BUTTONPRESSED);
}
