#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte pacman1[8] = {
B00000,
B00000,
B01110,
B11011,
B11100,
B11111,
B01110,
};

byte pacman2[8] = {
B00000,
B00000,
B01110,
B11011,
B11111,
B11111,
B01110,
};

byte ghost[8] = {
B00000,
B00000,
B01110,
B10101,
B11111,
B11111,
B10101,
};

byte food[8] = {
B00000,
B00000,
B00000,
B00110,
B00110,
B00000,
B00000,
};

//butonale
#define rightBtn     5
#define upBtn        6
#define downBtn      7
#define leftBtn      8

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buzzer = 8;

int xPac=0; // pozitia initiala pe linie 
int yPac=0; // pozitia initiala pe coloana

int v=0;
void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0, pacman1);
  lcd.createChar(1, pacman2);
  lcd.createChar(2, ghost);
  lcd.createChar(3, food);
}

void loop() {  
  //start();
  
  lcd.setCursor(xPac,yPac);
  lcd.write(byte(0));
  //lcd.setCursor(xPac+1,yPac);
  //lcd.write(byte(3));
 // lcd.scrollDisplayRight();
  //delay(300);
  int state=readBtn();
  switch (state) {
  case rightBtn:
    v=verify(xPac+1,yPac);
    if(v=1){
    //xPac=xPac+1;
    lcd.scrollDisplayRight();
    delay(300);
    }
    break;
  case upBtn:
    v=verify(xPac,yPac-1);
    if(v=1){
    yPac=yPac-1;
    }
    break;
  case downBtn:
    v=verify(xPac,yPac+1);
    if(v=1){
    yPac=yPac+1;
    }
    break;
  case leftBtn:
    v=verify(xPac-1,yPac);
    if(v=1){
   // xPac=xPac-1;
    lcd.scrollDisplayLeft();
     delay(300);
    }
    break;
  default:
    // statements
    break;
}
 // if(buttonState1 == LOW){
  // you_lose();
  //}
  //if(buttonState2 == LOW){
    //you_won();
    //level1();
  //}
}

void start(){ 
   lcd.setCursor(0, 0);
   lcd.print("     Pacman"); 
   lcd.setCursor(0, 1);  
  for(int i=0;i<16;i++){
    if(i>0){
      delay(200);
      lcd.setCursor(i-1,1);
      lcd.print(" ");
    }
    if(i == 0){
      delay(200);
      lcd.setCursor(15,1);
      lcd.print(" ");
    }
    if(i % 2 == 0){
    delay(200);
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    }else{
    delay(200);
    lcd.setCursor(i, 1);
    lcd.write(byte(1));
    }
  }
}

int verify(int x,int y){
  if(x<15 && y<2){
  return 1;
  }
  else{
  return 0;
  }
}

int readBtn(){
buttonState1=digitalRead(A1);
buttonState2=digitalRead(A2);
buttonState3=digitalRead(A3);
buttonState4=digitalRead(A4);
  
  if(buttonState1 == LOW){
    return leftBtn;
  }
  if(buttonState2 == LOW){
    return upBtn;
  }
  if(buttonState3 == LOW){
    return rightBtn;
  }
  if(buttonState4 == LOW){
    return downBtn;
  }
}

void you_won(){ 
lcd.setCursor(0,0);
lcd.print("       YOU");
lcd.setCursor(0,1); 
  lcd.print("       WON");
win_song();  
}

void level1(){
lcd.setCursor(0,0);
lcd.print("      LEVEL");
lcd.setCursor(0,1); 
  lcd.print("        1");
}

void you_lose(){
lcd.setCursor(0,0);
lcd.print("       YOU");
lcd.setCursor(0,1); 
  lcd.print("      LOSE");
lose_song();
}

void win_song(){
      tone(buzzer,420,200);
      delay(500);
      tone(buzzer,440,200);
      delay(500);
      tone(buzzer,490,270);
      delay(300);
      tone(buzzer,520,200);
      delay(300);
}

void lose_song(){
      tone(buzzer,190,230);
      delay(500);
      tone(buzzer,100,230);
      delay(500);
      tone(buzzer,50,270);
      delay(300);
}
 
