#include <LiquidCrystal.h>

#define btUP    A0
#define btOK    A1
#define btDOWN  A2
#define BUTTONPRESSED 0

#define btUP_pressed    1
#define btOK_pressed    2
#define btDOWN_pressed  3


#define MAXPASSOERRO 1000

#define DENTESPOLIA1 150
#define DENTESPOLIA2 36
#define RELACAOPOLIA 4
#define AVANCODOFUSOMM 1
#define DISTANCIAMM 50
#define PASSOSPARAVOLTA 200
#define HOME_STEP_PERIOD 10000
#define SLOW_STEP_PERIOD 5000


#define WELCOME 0
#define HOME1_1 1
#define HOME1_2 2
#define HOME2_1 3
#define HOME2_2 4
#define CONFIGA_1 11
#define CONFIGA_2 12
#define CONFIGB1_1 21
#define CONFIGB1_2 22
#define CONFIGB2_1 23
#define CONFIGB2_2 24
#define PROCESS_W 31
#define PROCESS_G 33
#define AJUDA_1 41

#define VERSAO "Rspidr_MRB_v0.2"

 
// defines pins numbers
#define fcHOME A4
#define STEPHOMEOFFSET 25

const int stepPin = 4; 
const int dirPin = 3; 
const int sleepPin = 5; 
const int resetPin = 6; 

volatile uint8_t btUP_state = !BUTTONPRESSED;
volatile uint8_t btOK_state = !BUTTONPRESSED;
volatile uint8_t btDOWN_state = !BUTTONPRESSED;


int currentPage = HOME1_1;




//Velocidade maxima

unsigned int passos_aceleracao = 20;
unsigned int periodo_us = 1500;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
//const int numerodepassos_avanco= DENTESPOLIA2*DISTANCIAMM*PASSOSPARAVOLTA/RELACAOPOLIA;
  int numerodepassos_avanco = 550;

// Variáveis do processo

int aceleracaoProc = 1;
int velocidadeProc = 1;
int ciclosPorMinuto = 8;
bool usePeriodUs = true;

// Define page

bool homeMade = false;
volatile char refreshFlag = false;
bool onGoingProcess = false;
